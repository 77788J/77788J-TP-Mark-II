// #ifndef CHASSIS_PROFILE_FOLLOWER_H_
// #define CHASSIS_PROFILE_FOLLOWER_H_

// #include "chassis.hpp"

// namespace chassis_profile_follower {

//   // constants
//   static const float VOLT_TO_DEG_MS = 0.0003f;

//   // movement statistics
//   extern float accel; // acceleration of motors (mv/ms^2)
//   extern float kp; // proportional tuning parameter for feedback control
//   extern float ki; // integral tuning parameter for feedback control

//   // currently in motion?
//   extern bool in_motion;

//   // controller for async movements
//   extern pros::Task* async_controller;
//   void async_controller_run(void* param);

//   // move for specific distance
//   void move_definite(float dist, float max_voltage=12000, float start_voltage=3000, bool syncronous=true);

//   // move indefitely
//   void move_indefinite(float max_voltage=12000, float start_voltage=3000, bool syncronous=true);

//   // rotate
//   void rotate_by(float degrees, float max_voltage, float start_voltage=3000, bool syncronous=true);

// }

// #endif