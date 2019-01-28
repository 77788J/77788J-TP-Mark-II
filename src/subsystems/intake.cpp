#include "../../include/subsystems/intake.hpp"
#include "../../include/field_managers/ball_tracker.hpp"

namespace intake {


  // motor
  pros::Motor motor(12, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);


  // state data
  int state = 0;
  Mode mode = MODE_OFF;


  // switch mode
  void set_mode(Mode new_mode) {
    if (mode != new_mode) {

      mode = new_mode;

      switch (mode) {
        case (MODE_OFF): state = 0; break;
        case (MODE_INTAKE): state = 1; break;
        case (MODE_OUTTAKE): state = -1; break;
        case (MODE_AUTO): break;
      }

      motor.move_voltage(state * 12000);
    }
  }


  // toggle on/off
  void toggle(Mode new_mode) { 
    if (new_mode == mode) set_mode(MODE_OFF);
    else set_mode(new_mode);
  }


  // update
  void update(int delta_t) {
    if (mode == MODE_AUTO) {

      if (
        ball_tracker::ball_count_basic > 0 &&
        abs(VISION_IMAGE_WIDTH/2 - ball_tracker::balls_basic[0].x_middle_coord) < VISION_IMAGE_WIDTH * .75f &&
        ball_tracker::balls_basic[0].y_middle_coord > AUTO_Y_THRESHOLD
      ) motor.move_voltage(12000);
      else motor.move_voltage(0);

    }
  }
}
