#include "../../include/main.h"
#include "../../include/subsystems/subsystems.hpp"

void initialize() {
  catapult::set_resting_position(catapult::resting_position);
}

void disabled() {}

void competition_initialize() {
  pros::delay(1500);
  catapult::set_resting_position(catapult::resting_position);
}
