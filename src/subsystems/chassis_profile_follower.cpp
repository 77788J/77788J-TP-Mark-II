#include "../../include/subsystems/chassis_profile_follower.hpp"

namespace chassis_profile_follower {

    // movement statistics
  float accel = 15; // acceleration of motors (mv/ms^2)
  float kp = 12.3; // proportional tuning parameter for feedback control
  float kp_turn = 40.0; // proportional tuning parameter for feedback control
  float kd = 10; // integral tuning parameter for feedback control
  float kd_turn = 14; // integral tuning parameter for feedback control


  // current motion statistics
  bool is_definite = true;
  float _dist = 0;
  float _max_voltage = 12000;
  float _start_voltage = 0;
  bool _rotating = false;


  // currently in motion?
  bool start_motion = false;
  bool in_motion = false;


  // controller for async movements
  pros::Task* async_controller;
  void async_controller_run(void* param) {
    while (true) {
      if (start_motion) {
        in_motion = true;
        start_motion = false;
        if (is_definite) move_definite(_dist, _max_voltage, _start_voltage, true);
        else move_indefinite(_max_voltage, _start_voltage, true);
        in_motion = false;
      }

      pros::delay(10);
    }
  }


  // move for specific distance
  void move_definite(float dist, float max_voltage, float start_voltage, bool syncronous) {

    // run in task if not syncronous
    if (!syncronous) {
      is_definite = true;
      _dist = dist;
      _max_voltage = max_voltage;
      _start_voltage = start_voltage;
      _rotating = false;
      start_motion = true;
    }
    else {

      // setup
      float start_pos = chassis::get_position(chassis::SIDE_BOTH);
      float dist_travelled = 0;
      float current_voltage = start_voltage;

      // do the thing
      if (dist > 0) {
        while (fabs(dist - dist_travelled) > 90 || fabs(chassis::get_velocity(chassis::SIDE_BOTH)) > 5) {
          if (dist_travelled < dist - dist_travelled) {
            current_voltage = clamp(current_voltage + accel * 10, 0, 12000);
          }
          else {
            current_voltage = clamp(kp * (dist - dist_travelled) - kd * chassis::get_velocity(chassis::SIDE_BOTH), 0, 12000);
          }
          chassis::move_voltage(current_voltage, current_voltage);
          pros::delay(10);
          dist_travelled = chassis::get_position(chassis::SIDE_BOTH) - start_pos;
        }
      }
      else {
        while (fabs(dist - dist_travelled) > 90 || fabs(chassis::get_velocity(chassis::SIDE_BOTH)) > 5) {
          if (dist_travelled > dist - dist_travelled) {
            current_voltage = clamp(current_voltage - accel * 10, -12000, 0);
          }
          else {
            current_voltage = clamp(kp * (dist - dist_travelled) - kd * chassis::get_velocity(chassis::SIDE_BOTH), -12000, 0);
          }
          chassis::move_voltage(current_voltage, current_voltage);
          pros::delay(10);
          dist_travelled = chassis::get_position(chassis::SIDE_BOTH) - start_pos;
        }
      }
    }
  }


  // move indefitely
  void move_indefinite(float max_voltage, float start_voltage, bool syncronous) {

    if (!syncronous) {
      is_definite = false;
      _max_voltage = max_voltage;
      _start_voltage = start_voltage;
      _rotating = false;
      start_motion = true;
    }
    else {

      // setup
      float dist_travelled = 0;
      float current_voltage = start_voltage;

      // ramp up
      while (fabs(current_voltage - max_voltage) > 100) {
        current_voltage = clamp(current_voltage + accel * sign(max_voltage), -12000, 12000);
        chassis::move_voltage(current_voltage, current_voltage);
      }
    }
  }


  // move for specific distance
  void rotate_by(float degrees, float max_voltage, float start_voltage, bool syncronous) {

    // run in task if not syncronous
    if (!syncronous) {
      is_definite = true;
      _dist = degrees;
      _max_voltage = max_voltage;
      _start_voltage = start_voltage;
      _rotating = true;
      start_motion = true;
    }
    else {

      // setup
      float start_pos = chassis::get_position(chassis::SIDE_BOTH_TURN);
      float dist = chassis::dist_to_angle(degrees * (PI / 180.f) * chassis::WHEEL_DIST / 2.f);
      float dist_travelled = 0;
      float current_voltage = start_voltage;
      printf("%f", dist);

      // do the thing
      if (dist > 0) {
        while (fabs(dist - dist_travelled) > 10 || fabs(chassis::get_velocity(chassis::SIDE_BOTH_TURN)) > 5) {
          if (dist_travelled < dist - dist_travelled) {
            current_voltage = clamp(current_voltage + accel * 10, 0, 12000);
          }
          else {
            current_voltage = clamp(kp_turn * (dist - dist_travelled) - kd_turn * chassis::get_velocity(chassis::SIDE_BOTH_TURN), 0, 12000);
          }
          chassis::move_voltage(-current_voltage, current_voltage);
          pros::delay(10);
          dist_travelled = chassis::get_position(chassis::SIDE_BOTH_TURN) - start_pos;
        }
      }
      else {
         while (fabs(dist - dist_travelled) > 10 || fabs(chassis::get_velocity(chassis::SIDE_BOTH_TURN)) > 5) {
          if (dist_travelled < dist - dist_travelled) {
            current_voltage = clamp(current_voltage - accel * 10, -12000, 0);
          }
          else {
            current_voltage = clamp(kp_turn * (dist - dist_travelled) - kd_turn * chassis::get_velocity(chassis::SIDE_BOTH_TURN), -12000, 0);
          }
          chassis::move_voltage(-current_voltage, current_voltage);
          pros::delay(10);
          dist_travelled = chassis::get_position(chassis::SIDE_BOTH_TURN) - start_pos;
        }
      }
    }
  }
}