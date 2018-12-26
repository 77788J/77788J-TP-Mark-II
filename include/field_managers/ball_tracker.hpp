#ifndef BALL_TRACKER_H_
#define BALL_TRACKER_H_

#include "../main.h"

namespace ball_tracker {

  // config
  static const int MAX_BALLS = 5; // maximum amount of balls to look for
  static const float SENSOR_ANGLE = -60; // angle of vision sensor (degrees)
  static const float SENSOR_HEIGHT = 12; // height of vision sensor from ground (inches)
  static const float DISTANCE_SCALAR = 1800; // scalar used to calculate distance to ball

  // signatures
  static const int BALL_SIG = 1;

  // stores all data of a ball
  typedef struct Ball {
    bool identified;
    float vision_x;
    float vision_y;
    float robot_x;
    float robot_dist;
    float width;
    float height;
  } Ball;

  // vision sensor
  extern pros::Vision vision_sensor;

  // array of balls
  extern int ball_count; // how many balls are currently visible
  extern Ball balls[MAX_BALLS]; // array of balls currently visible

  // calculate distance from vision y coordinate
  float calc_ball_dist(float center_y);

  // create ball object
  Ball create_ball(float vision_x, float vision_y, float width, float height);

  // upate ball list
  void update();

}

#endif