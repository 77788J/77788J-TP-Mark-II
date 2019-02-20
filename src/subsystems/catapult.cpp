#include "../../include/subsystems/catapult.hpp"
#include "../../include/subsystems/intake.hpp"


// calculate nearest coterminal angle
float calc_coterminal(float angle, int offset) {
  return angle + (360 * offset);
}


namespace catapult {


  // motor
  pros::Motor motor(17, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);


  // manual override
  int manual_override_voltage = OVERRIDE_DISABLED;
  bool in_macro = false;


  // where the catapult goes when it's not doing anything
  float resting_position = POSITION_LOAD * 7.f/3.f;


  // set resting position
  void set_resting_position(float new_position) {
    resting_position = new_position;
    motor.move_absolute(resting_position * REDUCTION, 100);
  }


  // fire
  void fire() {
    set_resting_position(calc_coterminal(resting_position, 1));
    intake::reset_balls();
  }


  // update
  void update() {
    if (manual_override_voltage == OVERRIDE_DISABLED) motor.move_absolute(resting_position * REDUCTION, 100);
    else motor.move_voltage(manual_override_voltage);
  }
}
