#ifndef CAP_TRACKER_H_
#define CAP_TRACKER_H_

#include "../main.h"

namespace cap_tracker {

  // config
  static const int MAX_CAPS = 5; // maximum amount of caps to look for
  static const float SENSOR_ANGLE = 208; // angle of vision sensor (degrees)
  static const float SENSOR_HEIGHT = 2.625; // height of vision sensor from ground (inches)
  // static const float DISTANCE_SCALAR = 1; // scalar used to calculate distance to cap

  // signatures
  static const int CAP_SIG_RED = 2;
  static const int CAP_SIG_BLUE = 1;
  
  // distances
  static const float flip_dist_cap = 20;
  static const float grab_dist_cap = 8;

  // possible cap colors
  enum Color {color_red, color_blue};

  // stores all data of a cap
  typedef struct Cap {
    bool identified;
    float vision_x;
    float vision_y;
    float robot_x;
    float robot_dist;
    float width;
    float height;
    Color color;
  } Cap;

  // vision sensor
  extern pros::Vision vision_sensor;

  // array of caps
  extern int cap_count; // how many caps are currently visible
  extern Cap caps[MAX_CAPS]; // array of caps currently visible

  // calculate distance from vision y coordinate
  float calc_cap_dist(float center_y);

  // create cap object
  Cap create_cap(float vision_x, float vision_y, float width, float height, Color color);

  // upate cap list
  void update();

}

#endif