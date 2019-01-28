#include "../../include/main.h"
#include "../../include/controller.hpp"
#include "../../include/field_managers/ball_tracker.hpp"
#include "../../include/field_managers/cap_tracker.hpp"
#include "../../include/field_managers/flag_tracker.hpp"
#include "../../include/subsystems/subsystems.hpp"

using namespace pros;


bool intake_auto = true;
bool flip_auto = false;
bool lift_auto = false;


// chassis control
void driver_chassis() {
  if (fabs(controller.analog_left_y) + fabs(controller.analog_right_y) <= 5) chassis::move_velocity(0, 0);
  else chassis::move_voltage(controller.analog_left_y * 12000, controller.analog_right_y * 12000);
}


// catapult control
void driver_catapult() {

  // manual override
  if (controller.btn_b) catapult::manual_override_voltage = -12000;
  else {
    catapult::manual_override_voltage = catapult::OVERRIDE_DISABLED;

    // fire on button press
    if (controller.btn_r1_new == 1) {
      catapult::fire();
      controller.controller.rumble(".");
    }
  }

  catapult::update();
}


// intake control
void driver_intake() {
  if (intake_auto) intake::set_mode(intake::MODE_AUTO);
  else if (controller.btn_r2_new == 1) intake::toggle(intake::MODE_INTAKE);
  else if (controller.btn_a_new == 1) intake::toggle(intake::MODE_OUTTAKE);

  intake::update(10);
}


// lift control
void driver_lift() {

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
  if (controller.btn_l1_new == -1)  {
    if (controller.btn_l1_hold_time > 100 && lift::get_height() >= lift::HEIGHT_MIN) lift::goto_height(lift::get_height());
    else lift::goto_height(lift::HEIGHT_MIN);
  }
  if (controller.btn_l2_new == -1 && controller.btn_l2_hold_time > 75) lift::goto_height(lift::get_height());
  if (controller.btn_up_new == 1) lift::flip_air();
  if (controller.btn_right_new == 1) lift::flip_ground();
  // if (controller.btn_down_new == 1) lift::goto_height(lift::HEIGHT_BRAKE);
  // if (controller.btn_down_new == -1) lift::goto_height(lift::HEIGHT_MIN);

  lift::update(10);
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

  // update driver control
   driver_chassis();
   driver_catapult();
   driver_intake();
   driver_lift();

  if (cap_tracker::cap_count >= 1) printf("%f\"\n", cap_tracker::caps[0].robot_dist);

  printf("%f\t%f\n", chassis::get_position(chassis::SIDE_LEFT), chassis::get_position(chassis::SIDE_RIGHT));
  if (ball_tracker::ball_count > 0) printf("x: %d\ty: %d\n", ball_tracker::balls_basic[0].x_middle_coord, ball_tracker::balls_basic[0].y_middle_coord);

  delay(10);
  }
}
