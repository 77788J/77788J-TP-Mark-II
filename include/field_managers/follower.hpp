#ifndef FOLLOWER_H_
#define FOLLOWER_H_

namespace follower {

  // ball following value
  static const float follow_dist_ball = 6;

  // cap following values
  static const float follow_dist_cap = 18;
  static const float flip_dist_cap = 12;
  static const float grab_dist_cap = 6;

  // flag following values
  static const float fire_dist_double = 36;
  static const float fire_dist_single_far = 144;
  static const float fire_dist_single_near = 18;

  // follow tuning parameters
  typedef struct FollowParams {
    float dist_mult; // multiplier used to determine voltage based on distance
    float turn_x_mult; // multiplier used to determine voltage based on relative x
    float turn_angle_mult; // multiplier used to determine voltage based on relative angle
  } FollowParams;

  // default parameters
  extern FollowParams defalut_params;

  // follow object step
  template <class Followable>
  void follow_step(Followable object_to_follow, float distance=0, FollowParams params=defalut_params);

}

#endif