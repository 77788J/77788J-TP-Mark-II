#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"


// void move_dist(float left, float right, float max_vel=300, bool wait=true, bool stop=true) {

//   chassis::move_voltage(max_vel * 20, max_vel * 20);
//   chassis::wait_for_completion(pros::millis() + 600 * max(fabs(left - chassis::get_position(chassis::SIDE_LEFT)), fabs(right - chassis::get_position(chassis::SIDE_RIGHT))) / max_vel);

// }


namespace autons {

  void auto_blue_flag_wait(bool park) {

    int time_start = pros::millis();

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
    pros::delay(1000);
    chassis::rotate_to_orientation(-91, 200);
    chassis::move_dist(13, 13, 200);
    pros::delay(1000);
    intake::set_mode(intake::MODE_OFF);

    while(pros::millis() - time_start < 14250) pros::delay(10);
    catapult::fire();
    pros::delay(300);
  }
}