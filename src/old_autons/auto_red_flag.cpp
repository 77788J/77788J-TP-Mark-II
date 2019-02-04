// #include "../../include/main.h"
// #include "../../include/autons.hpp"
// #include "../../include/subsystems/subsystems.hpp"


// namespace autons {

//   void auto_red_flag() {

//     chassis::set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     catapult::set_resting_position(catapult::resting_position);
//     lift::goto_height(lift::HEIGHT_MIN);
//     pros::delay(250);
//     catapult::set_resting_position(catapult::resting_position);
//     lift::goto_height(lift::HEIGHT_MIN);

//     // grab ball from cap
//     intake::set_mode(intake::MODE_INTAKE);
//     chassis::move_dist(10, 10, 300, true, false);
//     catapult::set_resting_position(catapult::resting_position);
//     chassis::move_dist(20, 20, 600, true, false);
//     chassis::move_dist(9, 9, 200, true, true);
//     pros::delay(500);
//     chassis::move_dist(-41, -41, 400, true, true);
//     pros::delay(500);
//     intake::set_mode(intake::MODE_OFF);

//     // shoot flags
//     chassis::rotate_to_orientation(86.69, 200, true, true);
//     pros::delay(500);
//     catapult::fire();
//     pros::delay(500);
//     chassis::rotate_to_orientation(95, 300);
//     pros::delay(250);

//     // turn bottom flag
//     intake::set_mode(intake::MODE_INTAKE);
//     chassis::move_dist(42, 42, 600, true, true);

//     // get back inline with cap
//     pros::delay(750);
//     chassis::move_dist(-18, -18, 600, true, true);
//     intake::set_mode(intake::MODE_OFF);

//     // flip cap
//     pros::delay(200);
//     chassis::rotate_to_orientation(180, 300, true, true);
//     pros::delay(250);
//     chassis::move_dist(-2, -2, 600, true, true);
//     lift::flip_ground();
//     pros::delay(500);

//     // flip middle flag
//     chassis::rotate_to_orientation(28);
//     chassis::move_dist(44);
//   }
// }