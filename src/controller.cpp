#include "../include/controller.hpp"
#include "../include/field_managers/flag_tracker.hpp"

// controller object
Joystick controller;


// update input (buttons, analog sticks)
void update_controller_inputs() {
  controller.update();
}


// update lcd
int last_update_lcd = pros::millis();
void update_controller_lcd() {
  if (pros::millis() - last_update_lcd >= 50) {

    // update shoot recommendation display
    if (RECOMMEND_ICONS) {
      if (flag_tracker::in_range_double_shot) controller.controller.set_text(0, 0, "○○ YES         ");
      else                                    controller.controller.set_text(0, 0, "○○ NO          ");
      if (flag_tracker::in_range_near_shot_mid ||
          flag_tracker::in_range_far_shot_mid)
                                              controller.controller.set_text(1, 0, "○  MID         ");
      else if (flag_tracker::in_range_near_shot_top ||
          flag_tracker::in_range_far_shot_top)
                                              controller.controller.set_text(1, 0, "○  TOP         ");
      else                                    controller.controller.set_text(1, 0, "○  NO          ");
    }
    else {
      if (flag_tracker::in_range_double_shot) controller.controller.set_text(0, 0, "DOUBLE: YES    ");
      else                                    controller.controller.set_text(0, 0, "DOUBLE: NO     ");
      if (flag_tracker::in_range_near_shot_mid ||
          flag_tracker::in_range_far_shot_mid)
                                              controller.controller.set_text(1, 0, "SINGLE: MID    ");
      else if (flag_tracker::in_range_near_shot_top ||
          flag_tracker::in_range_far_shot_top)
                                              controller.controller.set_text(1, 0, "SINGLE: TOP    ");
      else                                    controller.controller.set_text(1, 0, "SINGLE: NO     ");
    }

    // update last update
    last_update_lcd = pros::millis();
  }
}