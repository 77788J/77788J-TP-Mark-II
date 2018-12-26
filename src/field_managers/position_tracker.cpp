#include "../../include/field_managers/position_tracker.hpp"

namespace position_tracker {


  // sensors
  pros::ADIEncoder* enc_left;
  pros::ADIEncoder* enc_right;
  pros::ADIEncoder* enc_side;


  // known values
  float left_dist;
  float right_dist;
  float side_dist;


  // state
  float x = 0;
  float x_vel = 0;
  float y = 0;
  float y_vel = 0;
  long double orientation = 0;
  float orientation_deg = 0;
  long double angular_vel = 0;


  // initialize
  void init(float _x, float _y, float _orientation) {

    // init variables
    x = _x;
    y = _y;
    orientation = _orientation;

    // init encoders
    while (pros::millis() < 200) pros::delay(10); // ADI is unstable when program is first started
    pros::ADIEncoder enc_left_initializer('A', 'B', false); enc_left = &enc_left_initializer;
    pros::ADIEncoder enc_right_initializer('C', 'D', false); enc_right = &enc_right_initializer;
    pros::ADIEncoder enc_side_initializer('E', 'F', false); enc_side = &enc_side_initializer;
  }


  // update
  void update(int delta_t) {

    // calculate known values
    float dist = (ANGLE_TO_DIST((enc_left->get_value() + enc_right->get_value()) * .5f)); // distance travelled as measured by left/right encoders
    float dist_side_wheel = ANGLE_TO_DIST(enc_side->get_value()); // distance travelled as measured by side encoder
    long double prev_orientation = orientation;
    orientation = ORIENTATION_FROM_SIDE_DIST(enc_right->get_value(), enc_left->get_value()); // absolute robot orientation (radians)
    orientation_deg = orientation * (180/PI); // save a copy of the orientation in degrees as well
    long double delta_orientation = orientation - prev_orientation; // change in orientation since last update

    // define for later
    float absolute_delta_x = 0;
    float absolute_delta_y = 0;

    // if no change in angle, calculate linearly
    if(prev_orientation == orientation) {
      absolute_delta_x = dist * cos(orientation) + dist_side_wheel * cos(orientation + PI/2);
      absolute_delta_y = dist * sin(orientation) + dist_side_wheel * sin(orientation + PI/2);
    }

    // otherwise, calculate via arc-based algorithm
    else {

      // calculate values
      long double reference_angle = fabs(delta_orientation); // abs of delta_orientation
      float dist_side = dist_side_wheel - (SIDE_DIST * delta_orientation); // net dist of sideways wheel after that which is required for robot rotation
      float radius = fabs(dist / delta_orientation); // radius of left/right arc
      float radius_side = fabs(dist_side / delta_orientation); // radius of sideways arc

      // calculate reference delta positions
      float delta_x = cos(reference_angle - (PI * .5)) * radius;
      float delta_y = sin(reference_angle - (PI * .5)) * radius + radius;
      float delta_x_side = -cos(reference_angle) * radius_side + radius_side;
      float delta_y_side = sin(reference_angle) * radius_side;

      // mirror over applicable axes
      delta_x *= (dist < 0) ? -1 : 1;
      delta_y *= (dist * delta_orientation < 0) ? -1 : 1;
      delta_x_side *= (dist_side * delta_orientation > 0) ? -1 : 1;
      delta_y_side *= (dist_side < 0) ? -1 : 1;

      // combine sideways movement into standard
      delta_x += delta_x_side;
      delta_y += delta_y_side;

      // rotate relative to field (rather than bot)
      absolute_delta_x = (delta_x * cos(prev_orientation)) - (delta_y * sin(prev_orientation));
      absolute_delta_y = (delta_x * sin(prev_orientation)) + (delta_y * cos(prev_orientation));
    }

    // calculate new state
    x += absolute_delta_x;
    x_vel = (x_vel * .5f) + (absolute_delta_x * (1000.f/delta_t) * .5f);
    y += absolute_delta_y;
    y_vel = (y_vel * .5f) + (absolute_delta_y * (1000.f/delta_t) * .5f);
    angular_vel = (angular_vel * .5f) + (delta_orientation * (180.f/PI) * (1000.f/delta_t) * .5f);
  }
}