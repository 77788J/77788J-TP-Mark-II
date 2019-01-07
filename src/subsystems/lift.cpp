#include "../../include/subsystems/lift.hpp"

namespace lift {


  // status
  bool is_flipping = false;


  // motors
  pros::Motor motor_left(7, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_right(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);


  // convert between angle and height
  float calc_height(float angle) {
    return (ARM_LENGTH * sin(angle * .0174532925)) + HEIGHT_FULCRUM;
  }

  float calc_angle(float height) {
    return asin((height - HEIGHT_FULCRUM) / ARM_LENGTH) * 57.2957795;
  }


  // calculate absolute angle of lift (degrees)
  float get_angle() {
    return ANGLE_START + (motor_left.get_position() + motor_right.get_position()) * .5f / REDUCTION;
  }

  // calculate height of lift (inches)
  float get_height() {
    return calc_height(get_angle());
  }


  // goto positions
  void goto_angle(float degrees) {
    motor_left.move_absolute((degrees - ANGLE_START) * REDUCTION, 200.f);
    motor_right.move_absolute((degrees - ANGLE_START) * REDUCTION, 200.f);
  }

  void goto_height(float height, bool flipping) {
    if (!flipping) is_flipping = false;
    goto_angle(calc_angle(height));
  }
  

  // flip cap
  float flip_height = HEIGHT_FLIP_GROUND;
  float height_after_flip = HEIGHT_FLIP_START;
  void flip(float start_height, float end_height) {

    is_flipping = true;
    flip_height = start_height;
    height_after_flip = end_height;
    goto_height(HEIGHT_MAX, true);
  }

  void flip_air() {
    flip(HEIGHT_MAX, HEIGHT_FLIP_START);
  }

  void flip_ground() {
    flip(HEIGHT_FLIP_GROUND, HEIGHT_MIN);
  }


  // update
  void update(int delta_t) {
    if (is_flipping && get_height() >= flip_height - FLIP_BUFFER) {
      is_flipping = false;
      goto_height(height_after_flip);
    }
  }
}
