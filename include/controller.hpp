#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "lib/joystick.hpp"

#define RECOMMEND_ICONS false // false for text, true for icons

// controller object
extern Joystick controller;

// update input (buttons, analog sticks)
void update_controller_inputs();

// update output (lcd, rumble)
void update_controller_outputs();

#endif