#include "../../include/main.h"
#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"


namespace autons {

  void auto_blue_flag() {

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
    chassis::move_dist(39, 39);
    chassis::move_dist(-40, -40);
    intake::set_mode(intake::MODE_OFF);

    // jerk catapult
    catapult::manual_override_voltage = -6900;
    pros::delay(240);
    catapult::manual_override_voltage = catapult::OVERRIDE_DISABLED;
    pros::delay(240);

    // shoot flags
    chassis::rotate_to_orientation(-88.6);
    catapult::fire();
    pros::delay(500);

    // turn bottom flag
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(14, 14);
    intake::set_mode(intake::MODE_OFF);


    // flip cap
    chassis::rotate_to_orientation(-230);
    chassis::move_dist(-4.5, -4.5);
    lift::flip_ground();
    pros::delay(300);

    // move back
    chassis::move_dist(16);
    chassis::rotate_to_orientation(-97);

    // hit flag
    chassis::move_dist(43);
    chassis::move_dist(-24);

  }
}