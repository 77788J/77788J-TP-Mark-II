#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"

namespace autons {

  void auto_red_flag_wait(bool park) {

    int time_start = pros::millis();

    // move to ball
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(39.6, 39.6, 350);
    catapult::set_resting_position(catapult::resting_position);
    pros::delay(500);
    catapult::set_resting_position(catapult::resting_position);

    // move away from ball
    chassis::move_dist(-44, -44, 420);
    pros::delay(250);

    // aim and fire
    chassis::rotate_to_orientation(90, 200);
    pros::delay(250);
    chassis::move_dist(16, 16, 200);
    pros::delay(250);

    while (pros::millis() - time_start < 14250) pros::delay(10);
    intake::set_mode(intake::MODE_OFF);
    catapult::fire();
    pros::delay(300);
  }
}