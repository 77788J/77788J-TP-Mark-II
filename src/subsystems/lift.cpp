#include "../../include/subsystems/lift.hpp"

namespace lift {


  // motors
  pros::Motor motor_left(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_right(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);


  // convert between angle and height
  float calc_height(float angle) {
    return ARM_LENGTH * sin(angle);
  }

  float calc_angle(float height) {
    return asin(height / ARM_LENGTH);
  }


  // calculate height of lift (inches)
  float get_height() {
    return calc_height((motor_left.get_position() + motor_right.get_position()) * .5f);
  }


  // goto positions
  void goto_angle(float degrees) {
    motor_left.move_absolute(degrees * REDUCTION, 200.f);
    motor_right.move_absolute(degrees * REDUCTION, 200.f);
  }

  void goto_height(float height) {
    goto_angle(calc_angle(height));
  }


  // flip cap
  bool is_flipping = false;
  float height_after_flip = HEIGHT_FLIP_START;
  void flip(float end_height) {

    is_flipping = true;
    height_after_flip = end_height;
    goto_height(HEIGHT_MAX);
  }

  void flip() {
    flip(HEIGHT_FLIP_START);
  }


  // update
  void update(int delta_t) {
    if (is_flipping && get_height() >= HEIGHT_MAX - 2) {
      is_flipping = false;
      goto_height(height_after_flip);
    }
  }
}
