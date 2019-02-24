#include "../../include/main.h"
#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"


void autonomous() {

  catapult::set_resting_position(catapult::resting_position);
  lift::goto_height(lift::HEIGHT_MIN);
  pros::delay(500);
  chassis::set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  chassis::motor_back_left.tare_position();
  chassis::motor_back_right.tare_position();
  chassis::motor_front_left.tare_position();
  chassis::motor_front_right.tare_position();
  // catapult::motor.tare_position();
  autons::selected(autons::park);
  
}
