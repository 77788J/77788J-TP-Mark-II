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


  // position control
  void move_position_absolute(float left, float right, float max_vel) {
    motor_front_left.move_absolute(left, max_vel);
    motor_back_left.move_absolute(left, max_vel);
    motor_front_right.move_absolute(right, max_vel);
    motor_back_right.move_absolute(right, max_vel);
  }

  void move_position_relative(float left, float right, float max_vel) {
    motor_front_left.move_relative(left, max_vel);
    motor_back_left.move_relative(left, max_vel);
    motor_front_right.move_relative(right, max_vel);
    motor_back_right.move_relative(right, max_vel);
  }
}