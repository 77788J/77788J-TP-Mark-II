#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"

namespace autons {

  void auto_red_flag(bool park) {

    int start_time = pros::millis();

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
    intake::set_mode(intake::MODE_OFF);
    catapult::fire();
    pros::delay(300);

    // move to cap
    chassis::move_dist(-6, -6, 150);
    chassis::rotate_to_orientation(40, 200);
    chassis::move_dist(17.69, 17.69, 275);

    // scrape balls
    intake::set_mode(intake::MODE_INTAKE);
    lift::goto_height(lift::HEIGHT_MAX_SIZE);
    pros::delay(250);
    chassis::move_dist(-16, -16, 250);

    // flip cap
    chassis::move_dist(15, 15, 300);
    lift::goto_height(lift::HEIGHT_MIN);
    chassis::move_dist(16, 16, 300);
    pros::delay(250);
    chassis::rotate_to_orientation(35, 200);

    // wait for balls to be in catapult
    while (pros::millis() - start_time < 14000) pros::delay(10);
    intake::set_mode(intake::MODE_OFF);

    // shoot flags
    catapult::fire();
    pros::delay(500);
    
    // // turn own bottom flag
    // chassis::move_dist(-4, -4, 200);
    // chassis::rotate_to_orientation(0, 200);
    // chassis::move_dist(-17.2, -17.2, 420);
    // pros::delay(120);
    // chassis::rotate_to_orientation(96.69, 300);
    // chassis::move_dist(25, 25, 469);
    // pros::delay(100);
    // chassis::move_dist(-12, -12, 600);

    // // turn middle bottom flag
    // chassis::move_dist(-16, -16, 250);
    // chassis::rotate_to_orientation(169, 180);
    // lift::goto_height(lift::HEIGHT_MAX_SIZE);
    // chassis::move_dist(-44, -44, 420);
    // chassis::rotate_to_orientation(270, 200);
    // chassis::move_dist(-6.9, -6.9, 200);
    // chassis::move_dist(12, 12, 200);
  }
}