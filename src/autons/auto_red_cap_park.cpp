#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"
#include "../../include/macros.hpp"

namespace autons {

  void auto_red_cap_park(bool park) {

    catapult::set_resting_position(catapult::resting_position);
    lift::goto_height(lift::HEIGHT_MIN + 4);
    pros::delay(600);
    lift::goto_height(lift::HEIGHT_MIN + 4);
    catapult::set_resting_position(catapult::resting_position);
    pros::delay(600);
    catapult::set_resting_position(catapult::resting_position);
    lift::goto_height(lift::HEIGHT_MIN + 4);
    chassis::move_dist(19.25, 19.25, 300, true, true);
    pros::delay(500);
    chassis::rotate_to_orientation(90, 200, true, true);
    pros::delay(500);
    chassis::move_voltage(4000, 4000);
    pros::delay(1500);
    chassis::move_voltage(-12000, -12000);
    pros::delay(2200);
    chassis::move_velocity(0, 0);
    
  }
}