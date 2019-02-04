#include "../../include/main.h"
#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"


namespace autons {

  void auto_red_cap_feed() {

    // setup
    intake::set_mode(intake::MODE_OUTTAKE);
    chassis::set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    catapult::set_resting_position(catapult::resting_position);
    catapult::manual_override_voltage = 6900;
    pros::delay(500);
    intake::set_mode(intake::MODE_OUTTAKE);
    catapult::manual_override_voltage = catapult::OVERRIDE_DISABLED;
    catapult::set_resting_position(catapult::resting_position);
    lift::goto_height(lift::HEIGHT_MIN);
    pros::delay(750);
    intake::set_mode(intake::MODE_OUTTAKE);
    catapult::set_resting_position(catapult::resting_position);
    lift::goto_height(lift::HEIGHT_MIN);
    intake::set_mode(intake::MODE_OFF);

    // turn to cap
    chassis::rotate_to_orientation(-90);

    // grab ball from cap
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(44);

    // flip other cap
    chassis::rotate_to_orientation(0);
    intake::set_mode(intake::MODE_OFF);
    chassis::move_dist(-4);
    lift::flip_ground();
    pros::delay(269);

    // back out and navigate to parking tile
    chassis::rotate_to_orientation(-90);
    chassis::move_dist(-38);
    chassis::rotate_to_orientation(-180);
    chassis::move_dist(-34.5);
    chassis::rotate_to_orientation(-90);

    // park
    chassis::move_voltage(12000, 12000);
    pros::delay(2000);
    chassis::move_velocity(0, 0);
  }
}