// #include "../../include/main.h"
// #include "../../include/autons.hpp"
// #include "../../include/macros.hpp"
// #include "../../include/subsystems/subsystems.hpp"


// namespace autons {

//   void auto_cap_simple(bool park, bool red, bool get_other_crap) {

//     if (park) {

//       catapult::set_resting_position(catapult::resting_position);
//       lift::goto_height(lift::HEIGHT_MIN);
//       pros::delay(600);
//       lift::goto_height(lift::HEIGHT_MIN);
//       catapult::set_resting_position(catapult::resting_position);
//       pros::delay(600);
//       catapult::set_resting_position(catapult::resting_position);
//       lift::goto_height(lift::HEIGHT_MIN);
//       chassis::move_dist(19.25, 19.25, 300, true, true);
//       pros::delay(500);
//       chassis::rotate_to_orientation(-90, 200, true, true);
//       pros::delay(500);
//       chassis::move_voltage(-6000, -6000);
//       pros::delay(750);
//       chassis::move_voltage(12000, 12000);
//       pros::delay(2200);
//       chassis::move_velocity(0, 0);

//     }

//     else {

//       // shoot flag
//       if (!get_other_crap) pros::delay(11500);
//       catapult::set_resting_position(catapult::resting_position);
//       pros::delay(200);
//       catapult::set_resting_position(catapult::resting_position);
//       pros::delay(1000);
//       catapult::fire();
//       pros::delay(500);

//       if (get_other_crap) {

//         // turn to cap
//         if (red) chassis::rotate_to_orientation(-62, 250);
//         else chassis::rotate_to_orientation(62, 250);
//         pros::delay(500);

//         // grab ball from cap
//         intake::set_mode(intake::MODE_INTAKE);
//         chassis::move_dist(10, 10, 300, true, false);
//         catapult::set_resting_position(catapult::resting_position);
//         chassis::move_dist(20, 20, 600, true, false);
//         chassis::move_dist(9, 9, 200, true, true);
//         pros::delay(500);

//         // back up
//         chassis::move_dist(-18, -18, 420, true, true);
//         pros::delay(420);
//       }
//     }
//   }
// }