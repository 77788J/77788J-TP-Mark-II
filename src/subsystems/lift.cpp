#include "../../include/subsystems/lift.hpp"

namespace lift {


  // status
  bool is_flipping = false;
  float angle_start_calibrated = ANGLE_START;
  bool in_macro = false;


  // motors
  pros::Motor motor_left(16, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_right(15, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);


  // convert between angle and height
  float calc_height(float angle) {
    return (ARM_LENGTH * sin(angle * .0174532925)) + HEIGHT_FULCRUM;
  }
  float calc_angle(float height) {
    return asin((height - HEIGHT_FULCRUM) / ARM_LENGTH) * 57.2957795;
  }


  // calculate absolute angle of lift (degrees)
  float get_angle() {
    return angle_start_calibrated + (motor_left.get_position() + motor_right.get_position()) * .5f / REDUCTION;
  }

  // calculate height of lift (inches)
  float get_height() {
    return calc_height(get_angle());
  }


  // voltage control
  void move_voltage(float voltage) {
    motor_left.move_voltage(voltage);
    motor_right.move_voltage(voltage);
  }


  // goto positions
  void goto_angle(float degrees, float max_vel) {
    motor_left.move_absolute((degrees - angle_start_calibrated) * REDUCTION, max_vel);
    motor_right.move_absolute((degrees - angle_start_calibrated) * REDUCTION, max_vel);
  }

  void goto_height(float height, bool flipping, float max_vel) {
    if (!flipping) is_flipping = false;
    goto_angle(calc_angle(height), max_vel);
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
