#ifndef CHASSIS_H_
#define CHASSIS_H_

#include "../main.h"

namespace chassis {

  // motors
  extern pros::Motor motor_front_left;
  extern pros::Motor motor_back_left;
  extern pros::Motor motor_front_right;
  extern pros::Motor motor_back_right;

  // PWM control
  void move(float left, float right);

  // voltage control
  void move_voltage(float left, float right);

  // velocity control
  void move_velocity(float left, float right);

  // absolute position control
  void move_position_absolute(float left, float right, float max_vel);

  // absolute position control
  void move_position_absolute(float left, float right);

  // relative position control
  void move_position_relative(float left, float right, float max_vel);

  // relative position control
  void move_position_relative(float left, float right);

}

#endif