#include "../../include/subsystems/chassis.hpp"
#include "../../include/subsystems/chassis_profile_follower.hpp"

namespace chassis {
  
  
  // target positions
  float target_left = 0;
  float target_right = 0;

  
  bool in_macro = false;


  // motors
  pros::Motor motor_front_left(14, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_back_left(20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_front_right(18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_back_right(19, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);


  // initialize
  void init() {
    set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }


  // set brake mode
  void set_brake_mode(pros::motor_brake_mode_e mode) {
    motor_front_left.set_brake_mode(mode);
    motor_back_left.set_brake_mode(mode);
    motor_front_right.set_brake_mode(mode);
    motor_back_right.set_brake_mode(mode);
  }


  // sets current orientation to provided value (degrees)
  void set_orientation(float orientation) {
    float inches_reference = orientation * (PI / 180.f) * WHEEL_DIST * .5f;
    set_pos(-dist_to_angle(inches_reference), dist_to_angle(inches_reference));
  }


  // sets current position to provided value (degrees)
  void set_pos(float left, float right) {
    motor_front_left.set_zero_position(motor_front_left.get_position() - left);
    motor_back_left.set_zero_position(motor_back_left.get_position() - left);
    motor_front_right.set_zero_position(motor_front_right.get_position() - right);
    motor_back_right.set_zero_position(motor_back_right.get_position() - right);
  }


  // sets current distance to provided value (inches)
  void set_dist(float left, float right) {
    set_pos(angle_to_dist(left), angle_to_dist(right));
  }


  // PWM control
  void move(float left, float right) {
    motor_front_left.move(left);
    motor_back_left.move(left);
    motor_front_right.move(right);
    motor_back_right.move(right);
  }


  // voltage control
  void move_voltage(float left, float right) {
    motor_front_left.move_voltage(left);
    motor_back_left.move_voltage(left);
    motor_front_right.move_voltage(right);
    motor_back_right.move_voltage(right);
  }


  // velocity control
  void move_velocity(float left, float right) {
    motor_front_left.move_velocity(left);
    motor_back_left.move_velocity(left);
    motor_front_right.move_velocity(right);
    motor_back_right.move_velocity(right);
  }


  // relative orientation control (degrees)
  void rotate_by(float degrees, float max_voltage, bool wait, bool stop) {
    chassis_profile_follower::rotate_by(degrees, max_voltage, 3000, stop);
  }


  // absolute orientation control (degrees) 
  void rotate_to_orientation(float degrees, float max_voltage, bool wait, bool stop) {
    rotate_by(degrees - get_orientation(), max_voltage, wait, stop);
  }
  
  
  // move distance (relative) (inches)
 void move_dist(float dist, float max_voltage, float start_voltage, bool wait, bool stop) {
   float motor_dist = dist_to_angle(dist);
   if (stop) chassis_profile_follower::move_definite(motor_dist, max_voltage, start_voltage, wait);
   else chassis_profile_follower::move_indefinite(max_voltage, start_voltage, wait);
 }
    
    
  // wait for a movement to be finished
  void wait_for_completion(int end_time, float buffer) {
    bool compare_left = (target_left > get_position(SIDE_LEFT));
    bool compare_right = (target_right > get_position(SIDE_RIGHT));
    
    while ((((target_left > get_position(SIDE_LEFT)) == compare_left &&
              fabs(target_left - get_position(SIDE_LEFT)) > buffer) ||

             ((target_right > get_position(SIDE_RIGHT)) == compare_right &&
              fabs(target_right - get_position(SIDE_RIGHT)) > buffer)) &&
              pros::millis() <= end_time)
      
      pros::delay(10);
  }
}
