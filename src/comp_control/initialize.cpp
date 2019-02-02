#include "../../include/main.h"
#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"
#include "../../include/macros.hpp"

void update_stuffs(void* param) {
  while (true) {
    catapult::update();
    intake::update(10);
    lift::update(10);

    // cause the catapult seems to be ignored when the program starts occasionally
    if (pros::millis() % 1000 <= 10) catapult::set_resting_position(catapult::resting_position);

    pros::delay(10);
    }
}

void initialize() {
  catapult::set_resting_position(catapult::resting_position);
  lift::goto_height(lift::HEIGHT_MIN);
  chassis::init();
  pros::Task update(update_stuffs);
  pros::Task macros(macros::update);
}

void disabled() {}


namespace autons {
  Auton selected = AUTON_NONE;
  bool feed = false;
  bool park = true;
}

void competition_initialize() {
  pros::delay(1500);
  catapult::set_resting_position(catapult::resting_position);
  lift::goto_height(lift::HEIGHT_MIN);

  // lvgl
  // lv_obj_t* flag_red_btn = lv_btn_create(lv_scr_act(), NULL);
  // lv_btn_get_state(0);
  // lv_obj_t* flag_red_label = lv_label_create(flag_red_btn, NULL);
  // lv_label_set_text(flag_red_label, "RED FLAG");
}
