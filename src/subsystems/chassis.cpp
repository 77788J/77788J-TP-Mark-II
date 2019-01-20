#include "../../include/subsystems/chassis.hpp"

namespace chassis {
  
  
  // target positions
  float target_left = 0;
  float target_right = 0;


  // motors
  pros::Motor motor_front_left(13, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_back_left(15, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_front_right(2, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_back_right(4, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);


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


  // absolute position control (degrees)
  void move_position_absolute(float left, float right, float max_vel, bool wait, bool stop) {
    
    // set target variables
    target_left = left;
    target_right = right;

    // stop/continue movement
    if (stop) {
      motor_front_left.move_absolute(target_left, max_vel);
      motor_back_left.move_absolute(target_left, max_vel);
      motor_front_right.move_absolute(target_right, max_vel);
      motor_back_right.move_absolute(target_right, max_vel);
    }
    else move_velocity(max_vel, max_vel);

    // wait for completion
    if (wait) wait_for_completion();
  }


  // relative position control (degrees)
  void move_position_relative(float left, float right, float max_vel, bool wait, bool stop) {
    move_position_absolute(get_position(SIDE_LEFT) + left, get_position(SIDE_RIGHT) + right, max_vel, wait, stop);
  }
  
  
  // move distance (relative) (inches)
  void move_dist(float left, float right, float max_vel, bool wait, bool stop) {
    move_position_relative(dist_to_angle(left), dist_to_angle(right), max_vel, wait, stop);
  }


  // arc position control
  void move_arc(float radius, float angle, float max_vel, bool wait, bool stop) {
    long double angle_rad = angle * PI / 180;

    // calculate left/right distances
    float left_dist;
    float right_dist;
    if (radius > 0) {
      right_dist = angle_rad * (radius + WHEEL_DIST * .5f);
      left_dist = angle_rad * (radius - WHEEL_DIST * .5f);
    }
    else {
      left_dist = angle_rad * (radius + WHEEL_DIST * .5f);
      right_dist = angle_rad * (radius - WHEEL_DIST * .5f);
    }
    left_dist = dist_to_angle(left_dist);
    right_dist = dist_to_angle(right_dist);

    // calculate left/right final positions
    target_left = get_position(SIDE_LEFT) + left_dist;
    target_right = get_position(SIDE_RIGHT) + right_dist;

    // calculate left/right velocities
    float left_vel;
    float right_vel;
    if (radius > 0) {
      right_vel = max_vel;
      left_vel = max_vel * (left_dist / right_dist);
    }
    else {
      left_vel = max_vel;
      right_vel = max_vel * (right_dist / left_dist);
    }

    // stop/continue movement
    if (stop) {
      motor_front_left.move_absolute(target_left, left_vel);
      motor_back_left.move_absolute(target_left, left_vel);
      motor_front_right.move_absolute(target_right, right_vel);
      motor_back_right.move_absolute(target_right, right_vel);
    }
    else move_velocity(left_vel, right_vel);

    // wait for completion
    if (wait) wait_for_completion();
  }
    
    
  // wait for a movement to be finished
  void wait_for_completion(float buffer) {
    bool compare_left = (target_left > get_position(SIDE_LEFT));
    bool compare_right = (target_right > get_position(SIDE_RIGHT));
    
    while (((target_left > get_position(SIDE_LEFT)) == compare_left &&
             fabs(target_left - get_position(SIDE_LEFT)) > buffer) ||

             ((target_right > get_position(SIDE_RIGHT)) == compare_right &&
             fabs(target_right - get_position(SIDE_RIGHT)) > buffer))
      
      pros::delay(10);
  }
}
