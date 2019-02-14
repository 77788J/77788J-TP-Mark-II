#include "../../include/main.h"
#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"


namespace autons {

  void auto_red_cap() {

    // setup
    chassis::set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    catapult::set_resting_position(catapult::resting_position);
    catapult::manual_override_voltage = 6900;
    pros::delay(500);
    catapult::manual_override_voltage = catapult::OVERRIDE_DISABLED;
    catapult::set_resting_position(catapult::resting_position);
    lift::goto_height(lift::HEIGHT_MIN);
    pros::delay(750);
    catapult::set_resting_position(catapult::resting_position);
    lift::goto_height(lift::HEIGHT_MIN);

    // grab ball from cap
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(40);
    catapult::set_resting_position(catapult::resting_position);

    // flip other cap
    chassis::rotate_to_orientation(90);
    catapult::set_resting_position(catapult::resting_position);
    intake::set_mode(intake::MODE_OFF);
    chassis::move_dist(-4);
    lift::flip_ground();
    pros::delay(269);
    catapult::set_resting_position(catapult::resting_position);

    // back out and navigate to parking tile
    chassis::rotate_to_orientation(0);
    chassis::move_dist(-36);
    chassis::rotate_to_orientation(-90);
    catapult::set_resting_position(catapult::resting_position);
    chassis::move_dist(-27.25);
    chassis::rotate_to_orientation(0);

    // park
    chassis::move_voltage(12000, 12000);
    pros::delay(2000);
    catapult::set_resting_position(catapult::resting_position);
    chassis::move_velocity(0, 0);
  }
}