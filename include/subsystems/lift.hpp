#ifndef LIFT_H_
#define LIFT_H_

#include "../main.h"

namespace lift {

  // physical characteristics
  static const float ARM_LENGTH = 40.f; // length of lift arm (inches)
  static const float REDUCTION = 5.f; // gear reduction of lift (output/input)
  static const float FLIP_BUFFER = 1.5f; // buffer around flip height in which cap is considered flipped

  // heights
  static const float HEIGHT_MAX = 40.f; // maximum lift height (inches)
  static const float HEIGHT_FLIP_START = 30.f; // lift height where cap starts to flip (inches)
  static const float HEIGHT_LOW_POST = 20.f; // lift height where prongs are directly below low post cap (inches)
  static const float HEIGHT_FLIP_GROUND = 18.f; // lift height where cap is flipped on ground
  static const float HEIGHT_MIN = 12.f; // minimum lift height (before braking) (inches)
  static const float HEIGHT_BRAKE = 0.f; // lift height to engage brake (inches)

  // motors
  extern pros::Motor motor_left;
  extern pros::Motor motor_right;

  // convert between angle and height
  float calc_height(float angle); // calc lift height (inches) from angle (degrees)
  float calc_angle(float height); // calc lift angle (degrees) from height (inches)

  // calculate height of lift (inches)
  float get_height();

  // goto positions
  void goto_angle(float degrees); // goto angle (degrees)
  void goto_height(float height); // goto height (inches)

  // flip cap
  void flip(float start_height, float end_height); // flip cap, finishing at end_height
  void flip_air(); // flip cap, finishing at HEIGHT_FLIP_START
  void flip_ground(); // flip cap, finishing at HEIGHT_FLIP_START

  // update
  void update(int delta_t);

}

#endif