#ifndef CHASSIS_H_
#define CHASSIS_H_

#include "../main.h"

namespace chassis {

  // physical characteristics
  static const float WHEEL_DIST = 15.f; // distance between wheels (inches)
  static const float WHEEL_DIAM = 4.125f; // diameter of wheels (inches)
  static const float EXT_REDUCT = 7.f/3.f; // external gear reduction (wheel/motor)

  // sides
  enum Side {
    SIDE_LEFT,
    SIDE_RIGHT,
    SIDE_BOTH
  };

  // motors
  extern pros::Motor motor_front_left;
  extern pros::Motor motor_back_left;
  extern pros::Motor motor_front_right;
  extern pros::Motor motor_back_right;

  // get position (degrees) of a specified side
  inline float get_position(Side side) {
    if (side == SIDE_LEFT) return (motor_front_left.get_position() + motor_back_left.get_position()) * .5f;
    if (side == SIDE_RIGHT) return (motor_front_right.get_position() + motor_back_right.get_position()) * .5f;
    if (side == SIDE_BOTH) return (get_position(SIDE_LEFT) + get_position(SIDE_RIGHT)) * .5f;
    return 0;
  }

  // get velocity (rpm) of a specified side
  inline float get_velocity(Side side) {
    if (side == SIDE_LEFT) return (motor_front_left.get_actual_velocity() + motor_back_left.get_actual_velocity()) * .5f;
    if (side == SIDE_RIGHT) return (motor_front_right.get_actual_velocity() + motor_back_right.get_actual_velocity()) * .5f;
    if (side == SIDE_BOTH) return (get_velocity(SIDE_LEFT) + get_velocity(SIDE_RIGHT)) * .5f;
    return 0;
  }
  
  // convert angle (degrees) to distance (inches)
  inline float angle_to_dist(float angle) {
    return angle * PI/180 * WHEEL_DIAM * PI / EXT_REDUCT;
  }
  
  // convert distance (inches) to angle (degrees)
  inline float dist_to_angle(float dist) {
    return dist * EXT_REDUCT / (* PI/180 * WHEEL_DIAM * PI);
  }

  // PWM control
  void move(float left, float right);

  // voltage control
  void move_voltage(float left, float right);

  // velocity control
  void move_velocity(float left, float right);

  // absolute position control (degrees)
  void move_position_absolute(float left, float right, float max_vel=600, bool wait=true, bool stop=true);

  // relative position control (degrees)
  void move_position_relative(float left, float right, float max_vel=600, bool wait=true, bool stop=true);
  
  // move distance (relative) (inches)
  void move_dist(float left, float right, float max_vel=600, bool wait=true, bool stop=true);

  // arc position control
  void move_arc(float radius, float angle, float max_vel=600, bool wait=true, bool stop=true);

}

#endif
