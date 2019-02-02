#include "../../include/subsystems/chassis.hpp"

namespace chassis {
  
  
  // target positions
  float target_left = 0;
  float target_right = 0;

  
  bool in_macro = false;


  // motors
  pros::Motor motor_front_left(14, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_back_left(20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_front_right(18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_back_right(19, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);


  // initialize
  void init() {
    set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }


  // set brake mode
  void set_brake_mode(pros::motor_brake_mode_e mode) {
    motor_front_left.set_brake_mode(mode);
    motor_back_left.set_brake_mode(mode);
    motor_front_right.set_brake_mode(mode);
    motor_back_right.set_brake_mode(mode);
  }


  // PWM control
  void move(float left, float right) {
    motor_front_left.move(left);
    motor_back_left.move(left);
    motor_front_right.move(right);
    motor_back_right.move(right);
  }


  // voltage control
  void move_voltage(float left, float right) {
    motor_front_left.move_voltage(left);
    motor_back_left.move_voltage(left);
    motor_front_right.move_voltage(right);
    motor_back_right.move_voltage(right);
  }


  // velocity control
  void move_velocity(float left, float right) {
    motor_front_left.move_velocity(left);
    motor_back_left.move_velocity(left);
    motor_front_right.move_velocity(right);
    motor_back_right.move_velocity(right);
  }


  // relative orientation control (degrees)
  void rotate_by(float degrees, float max_vel, bool wait, bool stop) {
    float dist = degrees * (PI / 180.f) * WHEEL_DIST / 2.f;
    move_dist(-dist, dist, max_vel, wait, stop);
  }


  // absolute orientation control (degrees) 
  void rotate_to_orientation(float degrees, float max_vel, bool wait, bool stop) {
    rotate_by(degrees - get_orientation(), max_vel, wait, stop);
  }


  // absolute position control (degrees)
  void move_position_absolute(float left, float right, float max_vel, bool wait, bool stop) {
    
    // set target variables
    target_left = left;
    target_right = right;
    int end_time = pros::millis() + 650 * max(fabs(left - get_position(SIDE_LEFT)), fabs(right - get_position(SIDE_RIGHT))) / max_vel;

    // stop/continue movement
    if (stop) {
      motor_front_left.move_absolute(target_left, max_vel);
      motor_back_left.move_absolute(target_left, max_vel);
      motor_front_right.move_absolute(target_right, max_vel);
      motor_back_right.move_absolute(target_right, max_vel);
    }
    else move_velocity(max_vel, max_vel);

    // wait for completion
    if (wait) wait_for_completion(end_time);
  }


  // relative position control (degrees)
  void move_position_relative(float left, float right, float max_vel, bool wait, bool stop) {
    move_position_absolute(get_position(SIDE_LEFT) + left, get_position(SIDE_RIGHT) + right, max_vel, wait, stop);
  }
  
  
  // move distance (relative) (inches)
  void move_dist(float left, float right, float max_vel, bool wait, bool stop) {
    printf("%f\t%f\n", left,  right);
    move_position_relative(dist_to_angle(left), dist_to_angle(right), max_vel, wait, stop);
  }


  // arc position control
  void move_arc(float radius, float angle, float max_vel, bool wait, bool stop, bool generated) {
    long double angle_rad = angle * PI / 180 * (generated ? -sign(radius) : 1);

    // calculate left/right distances
    float left_dist;
    float right_dist;
    if (radius < 0) {
      right_dist = angle_rad * (fabs(radius) + WHEEL_DIST * .5f);
      left_dist = angle_rad * (fabs(radius) - WHEEL_DIST * .5f);
    }
    else {
      left_dist = angle_rad * (fabs(radius) + WHEEL_DIST * .5f);
      right_dist = angle_rad * (fabs(radius) - WHEEL_DIST * .5f);
    }
    left_dist = dist_to_angle(left_dist);
    right_dist = dist_to_angle(right_dist);

    // calculate left/right final positions
    target_left = get_position(SIDE_LEFT) + left_dist;
    target_right = get_position(SIDE_RIGHT) + right_dist;

    // calculate left/right velocities
    float left_vel;
    float right_vel;
    if (radius < 0) {
      right_vel = max_vel;
      left_vel = max_vel * (left_dist / right_dist);
    }
    else {
      left_vel = max_vel;
      right_vel = max_vel * (right_dist / left_dist);
    }

    // stop/continue movement
    // if (stop) {
    //   motor_front_left.move_absolute(target_left, left_vel);
    //   motor_back_left.move_absolute(target_left, left_vel);
    //   motor_front_right.move_absolute(target_right, right_vel);
    //   motor_back_right.move_absolute(target_right, right_vel);
    // }
    /*else*/ move_velocity(left_vel, right_vel);

    // wait for completion
    if (wait) wait_for_completion();
    if (stop) move_velocity(0, 0);
  }
    
    
  // wait for a movement to be finished
  void wait_for_completion(int end_time, float buffer) {
    bool compare_left = (target_left > get_position(SIDE_LEFT));
    bool compare_right = (target_right > get_position(SIDE_RIGHT));
    
    while ((((target_left > get_position(SIDE_LEFT)) == compare_left &&
              fabs(target_left - get_position(SIDE_LEFT)) > buffer) ||

             ((target_right > get_position(SIDE_RIGHT)) == compare_right &&
              fabs(target_right - get_position(SIDE_RIGHT)) > buffer)) &&
              pros::millis() <= end_time)
      
      pros::delay(10);
  }
}
