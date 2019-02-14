#include "../include/macros.hpp"

namespace macros {

  // current macro
  Macro current_macro = MACRO_NONE;

  // task
  void update(void * param) {
    while (true) {
      switch (current_macro) {
        case MACRO_STACK: stack(); break;
        case MACRO_RESET_CATAPULT: reset_catapult(); break;
        default: break;
      }
      current_macro = MACRO_NONE;
      pros::delay(10);
    }
  }


  // stack cap
  void stack() {

    // set macro variables
    chassis::in_macro = true;
    lift::in_macro = true;

    lift::goto_height(lift::HEIGHT_MAX);
    while (lift::get_height() < lift::HEIGHT_MAX - 1.f) pros::delay(10);
    chassis::move_voltage(3200, 3200);
    pros::delay(120);

    for (int i = 0; i < 100; i++) {
      lift::move_voltage((42.0 - lift::get_angle()) * 250);
      pros::delay(10);
    }

    chassis::in_macro = false;
    lift::in_macro = false;
  }


  // reset catapult
  void reset_catapult() {
    catapult::in_macro = true;
    catapult::manual_override_voltage = 1250;
    pros::delay(200);
    while (fabs(catapult::motor.get_actual_velocity()) > 5) pros::delay(10);
    catapult::motor.tare_position();
    catapult::resting_position = catapult::POSITION_LOAD * 7.f/3.f;
    catapult::set_resting_position(catapult::resting_position);
    catapult::manual_override_voltage = catapult::OVERRIDE_DISABLED;
    catapult::in_macro = false;
  }
}