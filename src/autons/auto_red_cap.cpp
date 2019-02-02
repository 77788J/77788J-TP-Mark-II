#include "../../include/main.h"
#include "../../include/autons.hpp"
#include "../../include/macros.hpp"
#include "../../include/subsystems/subsystems.hpp"


namespace autons {

  void auto_red_flag(bool feed) {

    int orientation_start = feed ? 90 : 0;
    
    // feed preload
    if (feed) {
      intake::set_mode(intake::MODE_OUTTAKE);
      pros::delay(750);
    }
    chassis::rotate_to_orientation(0 - orientation_start, 250);

    // grab ball from cap
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(10, 10, 300, true, false);
    catapult::set_resting_position(catapult::resting_position);
    chassis::move_dist(20, 20, 600, true, false);
    chassis::move_dist(9, 9, 200, true, true);
    pros::delay(500);

    // back up slightly
    chassis::move_dist(-10, -10, 300, true, true);
    pros::delay(420);
    chassis::rotate_to_orientation(180 - orientation_start, 400, true, true);

    // go up to and grab cap
    chassis::move_dist(-9, -9, 420, true, true);
    pros::delay(500);
    lift::goto_height(lift::HEIGHT_MAX_SIZE, false, 128);
    pros::delay(420);

    // go to post
    chassis::rotate_to_orientation(33 - orientation_start, 300, true, true);
    pros::delay(250);
    chassis::move_dist(-14, -14, 600, true, false);
    chassis::move_dist(-8, -8, 250, true, true);
    pros::delay(250);
    chassis::rotate_to_orientation(0 - orientation_start, 250, true, true);
    pros::delay(200);
    chassis::move_dist(-21, -21, 240, true, true);
    pros::delay(250);

    // stack on post
    macros::stack();
    chassis::move_voltage(0, 0);
    lift::move_voltage(0);
    pros::delay(100);

    // move to other cap
    chassis::move_dist(30, 30, 600, true, false);
    chassis::move_dist(9, 9, 300, true, true);
    pros::delay(250);
    chassis::rotate_to_orientation(133 - orientation_start, 320, true, true);
    pros::delay(200);
    chassis::move_dist(-16, -16, 400, true, true);
    pros::delay(250);

    // flip cap
    lift::flip_ground();
    pros::delay(500);

    // back up
    chassis::move_dist(16, 16, 300, true, true);
    pros::delay(250);

    // rotate to tile
    chassis::rotate_to_orientation(-90 - orientation_start, 300, true, true);

    // line up and park
    chassis::move_voltage(6000, 6000);
    pros::delay(750);
    chassis::move_dist(-54, -54, 600, true, true);
  }
  }