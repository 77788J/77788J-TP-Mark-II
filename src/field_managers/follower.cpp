#include "../../include/field_managers/follower.hpp"
#include "../../include/subsystems/chassis.hpp"

namespace follower {


  // default parameters
  FollowParams defalut_params = {
    .dist_mult = 1,
    .turn_x_mult = 1,
    .turn_angle_mult = 1
  };


  // follow object step
  template <class Followable>
  void follow_step(Followable object_to_follow, float distance, FollowParams params) {

    // calculate distance voltage
    int dist_volt = (object_to_follow.robot_dist - distance) * defalut_params.dist_mult;

    // calculate turning voltage
    int turn_volt = 0;
    try {turn_volt = -object_to_follow.vision_x * defalut_params.turn_x_mult;} catch (...) {} // try to turn based on vision x
    try {turn_volt = object_to_follow.robot_angele * defalut_params.turn_angle_mult;} catch (...) {} // try to turn based on relative angle

    // set chassis voltage
    chassis::move_voltage(dist_volt + turn_volt, dist_volt - turn_volt);
  }


}