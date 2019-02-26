#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"


// void move_dist(float left, float right, float max_vel=300, bool wait=true, bool stop=true) {

//   chassis::move_voltage(max_vel * 20, max_vel * 20);
//   chassis::wait_for_completion(pros::millis() + 600 * max(fabs(left - chassis::get_position(chassis::SIDE_LEFT)), fabs(right - chassis::get_position(chassis::SIDE_RIGHT))) / max_vel);

// }


namespace autons {

  void auto_blue_flag(bool park) {

    // move to ball
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(30.6, 30.6, 350, true, false);
    chassis::move_dist(7, 7, 200);
    catapult::set_resting_position(catapult::resting_position);
    pros::delay(1000);
    catapult::set_resting_position(catapult::resting_position);

    // move away from ball
    chassis::move_dist(-42, -42, 420);
    pros::delay(250);

    // aim and fire
    chassis::rotate_to_orientation(-96, 200);
    pros::delay(250);
    chassis::rotate_to_orientation(-91, 200);
    chassis::move_dist(13, 13, 200);
    pros::delay(690);
    intake::set_mode(intake::MODE_OFF);
    catapult::fire();
    pros::delay(300);

    // move to cap
    chassis::move_dist(-8, -8, 150);
    chassis::rotate_to_orientation(-53.69, 200);
    chassis::move_dist(15.69, 15.69, 275);

    // scrape balls
    intake::set_mode(intake::MODE_INTAKE);
    lift::goto_height(lift::HEIGHT_MAX_SIZE);
    pros::delay(250);
    chassis::move_dist(-16, -16, 200);
    pros::delay(750);

    // flip cap
    chassis::move_dist(15, 15, 300);
    lift::goto_height(lift::HEIGHT_MIN);
    chassis::move_dist(16, 16, 300);
    chassis::rotate_to_orientation(-63, 200);

    // wait for balls to be in catapult
    int timeout = pros::millis() + 1769;
    while (intake::in_catapult < 2 && pros::millis() < timeout) pros::delay(10);
    intake::set_mode(intake::MODE_OFF);

    // shoot flags
    catapult::fire();
    pros::delay(500);
    
    // // turn own bottom flag
    // chassis::move_dist(-4, -4, 200);
    // chassis::rotate_to_orientation(0, 200);
    // chassis::move_dist(-27.2, -27.2, 420);
    // pros::delay(120);
    // chassis::rotate_to_orientation(-96.69, 300);
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