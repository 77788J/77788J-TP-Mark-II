#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"

namespace autons {

  void auto_red_flag(bool park) {

    // move to ball
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(34.6, 34.6, 350);
    pros::delay(200);

    // move away from ball
    chassis::move_dist(-30, -30, 350);

    // aim and fire
    chassis::rotate_to_orientation(100, 200);
    intake::set_mode(intake::MODE_OFF);
    catapult::fire();
    pros::delay(250);
    chassis::rotate_to_orientation(90, 200);
    pros::delay(250);

    // move to cap
    chassis::move_dist(8.3, 8.3, 200);
    chassis::rotate_to_orientation(40, 200);
    chassis::move_dist(11.4, 11.4, 200);

    // scrape balls
    intake::set_mode(intake::MODE_INTAKE);
    lift::goto_height(lift::HEIGHT_MAX_SIZE);
    pros::delay(250);
    chassis::move_dist(-12, -12, 200);

    // flip cap
    chassis::move_dist(15, 15, 200);
    lift::goto_height(lift::HEIGHT_MIN);
    chassis::move_dist(3, 3, 175);

    // wait for balls to be in catapult
    int timeout = pros::millis() + 750;
    while (intake::in_catapult < 2 && pros::millis() < timeout) pros::delay(10);

    // shoot flags
    catapult::fire();
    pros::delay(250);
    
    // turn own bottom flag
    chassis::rotate_to_orientation(0, 200);
    chassis::move_dist(-17, -17, 300);
    chassis::rotate_to_orientation(90, 200);
    chassis::move_dist(26, 26, 350);

    // turn middle bottom flag
    chassis::move_dist(-15, -15, 250);
    chassis::rotate_to_orientation(180, 200);
    lift::goto_height(lift::HEIGHT_MAX_SIZE);
    chassis::move_dist(-44, -44, 350);
    chassis::rotate_to_orientation(266, 200);
    chassis::move_dist(-14, -14, 350);
  }
}