#include "../../include/main.h"
#include "../../include/controller.hpp"
#include "../../include/field_managers/ball_tracker.hpp"
#include "../../include/field_managers/cap_tracker.hpp"
#include "../../include/field_managers/flag_tracker.hpp"
#include "../../include/subsystems/subsystems.hpp"
#include "../../include/macros.hpp"

using namespace pros;


bool intake_auto = true;
bool flip_auto = false;
bool lift_auto = false;


// chassis control
void driver_chassis() {
  if (!chassis::in_macro) {
    if ((controller.btn_l1 || controller.btn_l2) && fabs(controller.analog_left_y) + fabs(controller.analog_right_y) <= .05f) {
      chassis::move_velocity(0, 0);
      chassis::set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }
    else {
      chassis::move_voltage(controller.analog_left_y * 12000, controller.analog_right_y * 12000);
      chassis::set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    }
  }
}


// catapult control
void driver_catapult() {

  // manual override
  if (controller.btn_b) catapult::manual_override_voltage = 0;
  else if (controller.btn_y_new == 1) macros::current_macro = macros::MACRO_RESET_CATAPULT;
  else if (!catapult::in_macro) {
    catapult::manual_override_voltage = catapult::OVERRIDE_DISABLED;

    // fire on button press
    if (controller.btn_r1_new == 1) {
      catapult::fire();
      controller.controller.rumble(".");
    }
  }
}


// intake control
void driver_intake() {
  if (intake_auto) {
    if (controller.btn_r2) intake::set_mode(intake::MODE_INTAKE);
    else if (controller.btn_a) intake::set_mode(intake::MODE_OUTTAKE);
    else intake::set_mode(intake::MODE_AUTO);
  }
  else if (controller.btn_r2_new == 1) intake::toggle(intake::MODE_INTAKE);
  else if (controller.btn_a_new == 1) intake::toggle(intake::MODE_OUTTAKE);
}


// lift control
void driver_lift() {
  if (!lift::in_macro) {

  // automatic control
    if ((flip_auto || lift_auto) && (cap_tracker::cap_count > 0)) {
      cap_tracker::Cap cap = cap_tracker::caps[0];
      if (fabs(cap.robot_x) < 6) {
        if (lift_auto && cap.robot_dist < cap_tracker::grab_dist_cap && lift::get_height() < lift::HEIGHT_LIFT_CAP) lift::goto_height(lift::HEIGHT_LIFT_CAP);
        else if (flip_auto && controller.btn_l2 && cap.robot_dist < cap_tracker::flip_dist_cap && !lift::is_flipping) lift::flip_ground();
      }
    }

    // manual control
    if (controller.btn_l1_new == 1) lift::goto_height(lift::HEIGHT_MAX);
    if (controller.btn_l2_new == 1) lift::goto_height(lift::HEIGHT_BRAKE);
    if (controller.btn_l2_new == -1)  {
      if (lift::get_height() >= lift::HEIGHT_MIN) lift::goto_height(lift::get_height());
      else lift::goto_height(lift::HEIGHT_MIN);
    }
    if (controller.btn_l1_new == -1) lift::goto_height(lift::get_height());
    if (controller.btn_up_new == 1) lift::goto_height(lift::HEIGHT_MAX_SIZE);
    if (controller.btn_right_new == 1) lift::flip_ground();
    // if (controller.btn_down_new == 1) lift::goto_height(lift::HEIGHT_BRAKE);
    // if (controller.btn_down_new == -1) lift::goto_height(lift::HEIGHT_MIN);
  }
}


void opcontrol() {

// init necessary stuff
catapult::set_resting_position(catapult::resting_position);
chassis::init();

 while (true) {

   // update controller
   controller.update();

  // update field managers
  ball_tracker::update();
  cap_tracker::update();
  flag_tracker::update_flags();
  flag_tracker::update_flagpoles();

  // cause the catapult seems to be ignored when the program starts occasionally
  if (pros::millis() % 1000 == 0) catapult::set_resting_position(catapult::resting_position);

  // macros
  if (controller.btn_b_new == 1) macros::current_macro = macros::MACRO_STACK;

  // update driver control
   driver_chassis();
   driver_catapult();
   driver_intake();
   driver_lift();

  delay(10);
  }
}
