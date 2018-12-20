#include "../../include/subsystems/intake.hpp"

namespace intake {


  // motor
  pros::Motor motor(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);


  // state data
  int state = 0;
  Mode mode = MODE_OFF;


  // switch mode
  void set_mode(Mode new_mode) {

    mode = new_mode;

    switch (mode) {
      case (MODE_OFF): state = 0; break;
      case (MODE_INTAKE): state = 1; break;
      case (MODE_OUTTAKE): state = -1; break;
      case (MODE_AUTO): break;
    }

    motor.move_voltage(state * 12000);
  }


  // toggle on/off
  void toggle(Mode new_mode) { 
    if (new_mode == mode) set_mode(MODE_OFF);
    set_mode(new_mode);
  }


  // update
  void update(int delta_t) {}

}
