#ifndef FOLLOWER_H_
#define FOLLOWER_H_

namespace follower {

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