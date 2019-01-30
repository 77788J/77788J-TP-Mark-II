#include "../../include/main.h"
#include "../../include/subsystems/subsystems.hpp"


void autonomous() {

  chassis::set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // grab ball from cap
  intake::set_mode(intake::MODE_INTAKE);
	chassis::move_dist(36, 36, 600, true, true);
	chassis::move_dist(-36, -36, 600, true, true);
  intake::set_mode(intake::MODE_OFF);

  // shoot flags
	chassis::rotate_to_orientation(90, 600, true, true);
  catapult::fire();
  pros::delay(500);

  // turn bottom flag
  intake::set_mode(intake::MODE_INTAKE);
	chassis::move_dist(38, 38, 600, true, true);
	chassis::rotate_to_orientation(105, 600, true, true);
	chassis::move_dist(14, 14, 600, true, true);

  // get back inline with cap
	chassis::move_dist(-14, -14, 600, true, true);
  intake::set_mode(intake::MODE_OFF);
	chassis::rotate_to_orientation(90, 600, true, true);
	chassis::move_dist(-14, -14, 600, true, true);

  // flip cap
	chassis::rotate_to_orientation(180, 600, true, true);
	chassis::move_dist(-10, -10, 600, true, true);
  lift::flip_ground();
  pros::delay(500);

  // shoot flags with whatever balls we may still have
	chassis::rotate_to_orientation(35, 200, true, true);
  catapult::fire();
  pros::delay(500);

  // move inline with parking tile
	chassis::rotate_to_orientation(90, 600, true, true);
	chassis::move_dist(-47, -47, 600, true, true);

  // park
	chassis::rotate_to_orientation(0, 400, true, true);
	chassis::move_dist(267, 267, 600, true, true);
}
