#ifndef CATAPULT_H_
#define CATAPULT_H_

#include "../main.h"

namespace catapult {

  // positions
  #define POSITION_LOAD 0 // loading angle of catapult (not slipgear)
  #define POSITION_SLIP 0 // slip angle of catapult (not slipgear)
  #define POSITION_RELEASE 0 // release angle of catapult (not slipgear)

  // gear reduction (output/input)
  #define REDUCTION 7.f/3.f

  // motor
  extern pros::Motor motor;

  // where the catapult goes when it's not doing anything
  extern float resting_position;

  // set resting position
  void set_resting_position(float new_position);

  // fire
  void fire();

}

#endif