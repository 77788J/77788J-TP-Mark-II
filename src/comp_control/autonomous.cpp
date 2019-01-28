#include "../../include/main.h"
#include "../../include/subsystems/subsystems.hpp"


void autonomous() {
	intake::set_mode(intake::MODE_INTAKE);
  chassis::move_dist(36, 36);
  chassis::move_dist(-36, -36);
  chassis::rotate_to_orientation(90);
  intake::set_mode(intake::MODE_OFF);
  catapult::fire();
  pros::delay(250);
  chassis::rotate_to_orientation(95);
  intake::set_mode(intake::MODE_INTAKE);
  chassis::move_dist(48, 48);
  pros::delay(125);
  chassis::move_dist(-24, -24);
  chassis::rotate_to_orientation(30);
  chassis::move_dist(24, 24);
  chassis::rotate_to_orientation(60);
  catapult::fire();
  pros::delay(250);
  chassis::move_dist(48, 48);
  chassis::move_dist(-12, -12);
}
