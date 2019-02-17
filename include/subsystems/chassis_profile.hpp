// #ifndef CHASSIS_H_
// #define CHASSIS_H_

// #include "../main.h"

// namespace chassis {

//   // physical characteristics
//   static const float WHEEL_DIST = 14.5f; // distance between wheels (inches)
//   static const float WHEEL_DIAM = 4.125f; // diameter of wheels (inches)
//   static const float EXT_REDUCT = 7.f/3.f; // external gear reduction (wheel/motor)

//   // sides
//   enum Side {
//     SIDE_LEFT,
//     SIDE_RIGHT,
//     SIDE_BOTH,
//     SIDE_BOTH_TURN
//   };

//   // target positions
//   extern float target_left;
//   extern float target_right;

//   extern bool in_macro;

//   // motors
//   extern pros::Motor motor_front_left;
//   extern pros::Motor motor_back_left;
//   extern pros::Motor motor_front_right;
//   extern pros::Motor motor_back_right;
  
//   // convert angle (degrees) to distance (inches)
//   inline float angle_to_dist(float angle) {
//     return angle * (PI/180.f) * WHEEL_DIAM * .5f / EXT_REDUCT;
//   }
  
//   // convert distance (inches) to angle (degrees)
//   inline float dist_to_angle(float dist) {
//     return (360.f * EXT_REDUCT * dist) / (WHEEL_DIAM * PI);
//   }

//   // get position (degrees) of a specified side
//   static inline float get_position(Side side) {
//     if (side == SIDE_LEFT) return (motor_front_left.get_position() + motor_back_left.get_position()) * .5f;
//     if (side == SIDE_RIGHT) return (motor_front_right.get_position() + motor_back_right.get_position()) * .5f;
//     if (side == SIDE_BOTH) return (get_position(SIDE_LEFT) + get_position(SIDE_RIGHT)) * .5f;
//     if (side == SIDE_BOTH_TURN) return (get_position(SIDE_RIGHT) - get_position(SIDE_LEFT)) * .5f;
//     return 0;
//   }

//   // get velocity (rpm) of a specified side
//   static inline float get_velocity(Side side) {
//     if (side == SIDE_LEFT) return (motor_front_left.get_actual_velocity() + motor_back_left.get_actual_velocity()) * .5f;
//     if (side == SIDE_RIGHT) return (motor_front_right.get_actual_velocity() + motor_back_right.get_actual_velocity()) * .5f;
//     if (side == SIDE_BOTH) return (get_velocity(SIDE_LEFT) + get_velocity(SIDE_RIGHT)) * .5f;
//     if (side == SIDE_BOTH_TURN) return (get_velocity(SIDE_RIGHT) - get_velocity(SIDE_LEFT)) * .5f;
//     return 0;
//   }

//   // get absolute angle
//   static inline float get_orientation() {
//     return (180.f / PI) * (angle_to_dist(get_position(SIDE_RIGHT)) - angle_to_dist(get_position(SIDE_LEFT))) / WHEEL_DIST;
//   }

//   // init
//   void init();

//   // set brake mode
//   void set_brake_mode(pros::motor_brake_mode_e mode);

//   // sets current orientation to provided value (degrees)
//   void set_orientation(float orientation=0);

//   // sets current position to provided value (degrees)
//   void set_pos(float left=0, float right = 0);

//   // sets current distance to provided value (inches)
//   void set_dist(float left=0, float right=0);

//   // PWM control
//   void move(float left, float right);

//   // voltage control
//   void move_voltage(float left, float right);

//   // velocity control
//   void move_velocity(float left, float right);


//   // relative orientation control (degrees)
//   void rotate_by(float degrees, float max_vel=600, bool wait=true, bool stop=true);

//   // absolute orientation control (degrees) 
//   void rotate_to_orientation(float degrees, float max_voltage=12000, bool wait=true, bool stop=true);
  
//   // move distance (relative) (inches)
//   void move_dist(float dist, float max_voltage=12000, float start_voltage=0, bool wait=true, bool stop=true);
  
//   // wait for a movement to be finished
//   void wait_for_completion(int timeout=60000, float dist_buffer=.25f);

// }

// #endif
