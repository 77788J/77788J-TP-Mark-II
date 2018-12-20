#include "../../include/subsystems/catapult.hpp"


// calculate nearest coterminal angle
float calc_nearest_coterminal(float angle, int offset, float reduction) {
  float revolution = 360.f * reduction;
  float reference = floor(angle / revolution) * revolution;
  return reference + angle + (offset * revolution);
}


namespace catapult {


  // motor
  pros::Motor motor(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);


  // where the catapult goes when it's not doing anything
  float resting_position = POSITION_LOAD;


  // set resting position
  void set_resting_position(float new_position) {
    resting_position = new_position;
    motor.move_absolute(resting_position, 200);
  }


  // fire
  void fire() {
    set_resting_position(calc_nearest_coterminal(resting_position, 1, REDUCTION));
  }
}
