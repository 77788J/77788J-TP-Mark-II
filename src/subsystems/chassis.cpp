#include "../../include/subsystems/chassis.hpp"

namespace chassis {


  // motors
  pros::Motor motor_front_left(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_back_left(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_front_right(3, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
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


  // absolute position control
  void move_position_absolute(float left, float right, float max_vel, bool wait, bool stop) {

    // stop/continue movement
    if (stop) {
      motor_front_left.move_absolute(left, max_vel);
      motor_back_left.move_absolute(left, max_vel);
      motor_front_right.move_absolute(right, max_vel);
      motor_back_right.move_absolute(right, max_vel);
    }
    else move_velocity(max_vel, max_vel);

    // wait for finish
    if (wait) {
      bool compare_left = (left > get_position(SIDE_LEFT));
      bool compare_right = (right > get_position(SIDE_RIGHT));
        while ((left > get_position(SIDE_LEFT)) == compare_left || (right > get_position(SIDE_RIGHT)) == compare_right) pros::delay(10);
    }
  }


  // relative position control
  void move_position_relative(float left, float right, float max_vel, bool wait, bool stop) {
    move_position_absolute(get_position(SIDE_LEFT) + left, get_position(SIDE_RIGHT) + right, max_vel, wait, stop);
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

    // calculate left/right final positions
    float left_final = get_position(SIDE_LEFT) + left_dist;
    float right_final = get_position(SIDE_RIGHT) + right_dist;

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
      motor_front_left.move_absolute(left_final, left_vel);
      motor_back_left.move_absolute(left_final, left_vel);
      motor_front_right.move_absolute(right_final, right_vel);
      motor_back_right.move_absolute(right_final, right_vel);
    }
    else move_velocity(left_vel, right_vel);

    // wait for finish
    if (wait) {
      bool compare_left = (left_final > get_position(SIDE_LEFT));
      bool compare_right = (right_final > get_position(SIDE_RIGHT));
        while ((left_final > get_position(SIDE_LEFT)) == compare_left || (right_final > get_position(SIDE_RIGHT)) == compare_right) pros::delay(10);
    }
  }
}