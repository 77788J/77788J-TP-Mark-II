#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"

namespace autons {

  void auto_skills(bool park) {

    // move to ball
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(33.6, 33.6, 369);
    chassis::move_dist(8, 8, 200);
    catapult::set_resting_position(catapult::resting_position);
    pros::delay(500);
    catapult::set_resting_position(catapult::resting_position);

    // move away from ball
    chassis::move_dist(-46, -46, 420);
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
    chassis::move_dist(17, 17, 275);

    // scrape balls
    intake::set_mode(intake::MODE_INTAKE);
    lift::goto_height(lift::HEIGHT_MAX_SIZE);
    pros::delay(250);
    chassis::move_dist(-16, -16, 250);

    // flip cap
    chassis::move_dist(15, 15, 300);
    lift::goto_height(lift::HEIGHT_MIN);
    pros::delay(100);
    chassis::move_dist(12, 12, 300);
    chassis::move_dist(-14,-14, 300);

    // wait for balls to be in catapult
    pros::delay(750);

    // move to position
    chassis::rotate_to_orientation(-10, 200);
    chassis::move_dist(34, 34, 200);

    // shoot flags
    chassis::rotate_to_orientation(82.5, 200);
    chassis::move_dist(-6, -6, 200);
    catapult::fire();
    pros::delay(500);
    
    // go to cap
    chassis::move_dist(6, 6, 200);
    chassis::rotate_to_orientation(-10, 200);
    pros::delay(250);
    chassis::motor_front_left.tare_position();
    chassis::motor_back_left.tare_position();
    chassis::motor_back_right.tare_position();
    chassis::motor_front_right.tare_position();
    chassis::move_dist(34, 34, 300);

    // scrape ball(s)
    intake::set_mode(intake::MODE_INTAKE);
    lift::goto_height(lift::HEIGHT_MAX_SIZE);
    pros::delay(250);
    chassis::move_dist(-15, -15, 175);
    pros::delay(1000);

    // flip cap
    chassis::move_dist(18, 18, 200);
    lift::goto_height(lift::HEIGHT_MIN);
    chassis::move_dist(9, 9, 200);

    // shoot flags
    chassis::rotate_to_orientation(90, 200);
    chassis::move_dist(-4, -4, 200);
    intake::set_mode(intake::MODE_OFF);
    pros::delay(500);
    catapult::fire();
    pros::delay(500);

    // move back and turn
    chassis::move_dist(-14, -14, 200);
    chassis::rotate_to_orientation(186, 200);

    // get ball
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(26, 26, 420);
    pros::delay(500);
    chassis::move_dist(-26.5, -26.5, 420);
    pros::delay(250);

    // shoot flag
    chassis::rotate_to_orientation(90, 200);
    chassis::move_dist(32, 32, 300);
    pros::delay(750);
    catapult::fire();
    pros::delay(500);
    chassis::rotate_to_orientation(100, 200);

    // get bottom flag
    chassis::move_voltage(4000, 4000);
    pros::delay(2500);
    chassis::move_voltage(0, 0);
    pros::delay(250);
    chassis::motor_front_left.tare_position();
    chassis::motor_back_left.tare_position();
    chassis::motor_back_right.tare_position();
    chassis::motor_front_right.tare_position();

    // navigate to parking area
    chassis::move_dist(-48, -48, 300);
    chassis::rotate_to_orientation(-90, 200);
    chassis::move_dist(20, 20, 269);
    chassis::rotate_to_orientation(-190, 200);
    chassis::move_dist(38, 38, 200);
    chassis::rotate_to_orientation(-90, 200);
    lift::goto_height(lift::HEIGHT_MIN);

    // park
    chassis::move_voltage(4000, 4000);
    pros::delay(2000);
    lift::goto_height(lift::HEIGHT_MIN + 4);
    pros::delay(500);
    chassis::move_dist(-94, -94, 600);
  }
}