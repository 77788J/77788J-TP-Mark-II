#ifndef CATAPULT_H_
#define CATAPULT_H_

#include "../main.h"

namespace catapult {

  // positions
  static const float POSITION_LOAD = 62.69f; // loading angle of catapult (not slipgear)
  static const float POSITION_SLIP = 80; // slip angle of catapult (not slipgear)
  static const float POSITION_RELEASE = 0; // release angle of catapult (not slipgear)

  // gear reduction (output/input)
  static const float REDUCTION = 3.f;

  // manual override disable
  static const float OVERRIDE_DISABLED = 12001;

  // motor
  extern pros::Motor motor;

  // manual override
  extern int manual_override_voltage;
  extern bool in_macro;

  // where the catapult goes when it's not doing anything
  extern float resting_position;

  // set resting position
  void set_resting_position(float new_position);

  // fire
  void fire();

  // update
  void update();

}

#endif