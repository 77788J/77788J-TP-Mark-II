#include "../../include/main.h"
#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"


void autonomous() {

  catapult::set_resting_position(catapult::resting_position);
  lift::goto_height(lift::HEIGHT_MIN);
  pros::delay(500);
  chassis::set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  autons::selected(autons::park);
  
}
