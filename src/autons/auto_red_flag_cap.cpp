#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"
#include "../../include/macros.hpp"

namespace autons {

  void auto_red_cap(bool park) {

    // move to ball
    intake::set_mode(intake::MODE_INTAKE);
    chassis::move_dist(34.6, 34.6, 350);
    pros::delay(200);

    // move away from cap and rotate to pick it up
    chassis::move_dist(-9.5, -9.5, 200);
    chassis::rotate_to_orientation(180, 200);
    intake::set_mode(intake::MODE_OFF);
    pros::delay(500);

    // grab cap
    chassis::move_dist(-8.3, -8.3, 200);
    lift::goto_height(lift::HEIGHT_MAX_SIZE);

    // go to post
    chassis::move_dist(-12.5, -12.5, 175);
    chassis::rotate_to_orientation(90, 150);
    chassis::move_dist(-12, -12, 175);
    lift::goto_height(lift::HEIGHT_MAX);
    pros::delay(300);
    chassis::move_dist(-12, -12, 175);

    // stack on post
    float dist = chassis::angle_to_dist(chassis::get_position(chassis::SIDE_BOTH));
    macros::stack();
    lift::goto_height(lift::HEIGHT_MAX_SIZE);
    float target = dist - chassis::angle_to_dist(chassis::get_position(chassis::SIDE_BOTH)) - 4;
    chassis::move_dist(target, target, 200);

    // go to cap and flip
    chassis::rotate_to_orientation(0, 200);
    chassis::move_dist(13.5, 13.5, 250);
    lift::goto_height(lift::HEIGHT_MIN);
    pros::delay(250);

    // park if applicable
    if (park) {
      chassis::rotate_to_orientation(90, 200);
      chassis::move_voltage(-4000, 4000);
      pros::delay(250);
      chassis::move_dist(21, 21, 400);
      chassis::move_dist(29, 29, 600);
    }
  }
}