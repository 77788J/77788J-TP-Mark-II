#include "../../include/main.h"
#include "../../include/master.hpp"
#include "../../include/field_managers/cap_tracker.hpp"
#include "../../include/subsystems/subsystems.hpp"

using namespace pros;


bool intake_auto = true;
bool flip_auto = true;
bool lift_auto = true;


// define controller
Joystick controller;


// chassis control
void driver_chassis() {
  chassis::move(controller.analog_left_y, controller.analog_right_y);
}


// catapult control
void driver_catapult() {
  if (controller.btn_r1_new == 1) catapult::fire();
}


// intake control
void driver_intake() {
  if (intake_auto) intake::set_mode(intake::MODE_AUTO);
  else if (controller.btn_up_new == 1) intake::toggle(intake::MODE_INTAKE);
  else if (controller.btn_down_new == 1) intake::toggle(intake::MODE_OUTTAKE);
}


// lift control
void driver_lift() {

  // automatic control
  if (cap_tracker::cap_count > 0) {
    cap_tracker::Cap cap = cap_tracker::caps[0];
    if (fabs(cap.robot_x) < 6) {
      if (flip_auto && cap.robot_dist < cap_tracker::grab_dist_cap && lift::get_height() < lift::HEIGHT_LIFT_CAP) lift::goto_height(lift::HEIGHT_LIFT_CAP);
      else if (lift_auto && controller.btn_l1 && cap.robot_dist < cap_tracker::flip_dist_cap && !lift::is_flipping) lift::flip_ground();
    }
  }

  // manual control
  if (controller.btn_l1_new == 1) lift::goto_height(lift::HEIGHT_FLIP_START);
  if (controller.btn_l2_new == 1) lift::goto_height(lift::HEIGHT_MIN);
  if (controller.btn_l1_new == -1 && controller.btn_l1_hold_time > 250) lift::goto_height(lift::get_height());
  if (controller.btn_l2_new == -1 && controller.btn_l2_hold_time > 250) lift::goto_height(lift::get_height());
}


void opcontrol() {
 while (true) {

   controller.update();

   driver_chassis();
   driver_catapult();
   driver_intake();
   driver_lift();


    delay(10);
  }
}
