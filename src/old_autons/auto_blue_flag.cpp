// #include "../../include/main.h"
// #include "../../include/autons.hpp"
// #include "../../include/subsystems/subsystems.hpp"


// namespace autons {

//   void auto_blue_flag() {

//     chassis::set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     lift::goto_height(lift::HEIGHT_MIN);
//     catapult::set_resting_position(catapult::resting_position);
//     pros::delay(250);
//     catapult::set_resting_position(catapult::resting_position);
//     lift::goto_height(lift::HEIGHT_MIN);

//     // grab ball from cap
//     intake::set_mode(intake::MODE_INTAKE);
//     chassis::move_dist(10, 10, 300, true, false);
//     catapult::set_resting_position(catapult::resting_position);
//     chassis::move_dist(18, 18, 600, true, false);
//     chassis::move_dist(11, 11, 200, true, true);
//     pros::delay(500);
//     chassis::move_dist(-38.69, -38.69, 400, true, true);
//     pros::delay(500);

//     // shoot flags
//     chassis::rotate_to_orientation(-90, 200, true, true);
//     intake::set_mode(intake::MODE_OFF);
//     pros::delay(500);
//     catapult::fire();
//     pros::delay(500);
//     chassis::rotate_to_orientation(-101.5, 300);
//     pros::delay(250);

//     // turn bottom flag
//     intake::set_mode(intake::MODE_INTAKE);
//     chassis::move_dist(42, 42, 600, true, true);

//     // get back inline with cap
//     pros::delay(750);
//     chassis::move_dist(-17, -17, 600, true, true);
//     intake::set_mode(intake::MODE_OFF);

//     // flip cap
//     pros::delay(200);
//     chassis::rotate_to_orientation(-190, 300, true, true);
//     pros::delay(250);
//     chassis::move_dist(-8, -8, 600, true, true);
//     lift::flip_ground();
//     pros::delay(500);

//     // // shoot flags with whatever balls we may still have
//     // chassis::rotate_to_orientation(-50, 300, true, true);
//     // pros::delay(250);
//     // catapult::fire();
//     // pros::delay(500);

//     // // move inline with parking tile
//     // chassis::rotate_to_orientation(-105, 350, true, true);
//     // pros::delay(250);
//     // chassis::move_dist(-48, -48, 600, true, true);

//     // // park
//     // pros::delay(300);
//     // lift::goto_height(lift::HEIGHT_MAX_SIZE - 8, lift::HEIGHT_MAX_SIZE - 8);
//     // chassis::rotate_to_orientation(-200, 400, true, true);
//     // pros::delay(250);
//     // chassis::move_voltage(6000, 6000);
//     // pros::delay(750);
//     // chassis::move_voltage(-12000, -12000);
//     // pros::delay(1500);
//     // chassis::move_velocity(0, 0);
//   }
// }