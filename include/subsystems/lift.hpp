#ifndef LIFT_H_
#define LIFT_H_

#include "../main.h"

namespace lift {

  // physical characteristics
  static const float ARM_LENGTH = 16.5f; // length of lift arm (inches)
  static const float REDUCTION = 7.f; // gear reduction of lift (output/input)
  static const float FLIP_BUFFER = .5f; // buffer around flip height in which cap is considered flipped
  static const float HEIGHT_FULCRUM = 15.625; // height of lift fulcrum off ground
  static const float ANGLE_START = -42.f; // angle that lift starts at

  // heights
  static const float HEIGHT_MAX = 32.f; // maximum lift height (inches)
  static const float HEIGHT_FLIP_START = 26.f; // lift height where cap starts to flip (inches)
  static const float HEIGHT_LOW_POST = 22.f; // lift height where prongs are directly below low post cap (inches)
  static const float HEIGHT_MAX_SIZE = 14.f; // lift height where prongs are directly below low post cap (inches)
  static const float HEIGHT_FLIP_GROUND = 10.5f; // lift height where cap is flipped on ground
  static const float HEIGHT_LIFT_CAP = 9.f; // minimum lift height where held cap is off ground (inches)
  static const float HEIGHT_PARK = 7.69f; // minimum lift height before braking (inches)
  static const float HEIGHT_MIN = 5.85f; // minimum lift height before braking (inches)
  static const float HEIGHT_BRAKE = 3.3; // lift height to engage brake (inches)

  // status
  extern bool is_flipping;
  extern float angle_start_calibrated;
  extern bool in_macro;

  // motors
  extern pros::Motor motor_left;
  extern pros::Motor motor_right;

  // convert between angle and height
  float calc_height(float angle); // calc lift height (inches) from angle (degrees)
  float calc_angle(float height); // calc lift angle (degrees) from height (inches)

  // calculate absolute angle of lift (degrees)
  float get_angle();

  // calculate height of lift (inches)
  float get_height();

  // move voltage
  void move_voltage(float voltage);

  // goto positions
  void goto_angle(float degrees, float max_vel=200); // goto angle (degrees)
  void goto_height(float height, bool flipping=false, float max_vel=200); // goto height (inches)

  // flip cap
  void flip(float start_height, float end_height); // flip cap, finishing at end_height
  void flip_air(); // flip cap, finishing at HEIGHT_FLIP_START
  void flip_ground(); // flip cap, finishing at HEIGHT_FLIP_START

  // update
  void update(int delta_t);

}

#endif