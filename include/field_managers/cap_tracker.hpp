#ifndef CAP_TRACKER_H_
#define CAP_TRACKER_H_

#include "../main.h"

namespace cap_tracker {

  // config
  #define MAX_CAPS 5 // maximum amount of caps to look for
  #define SENSOR_ANGLE -60 // angle of vision sensor (degrees)
  #define SENSOR_HEIGHT 12 // height of vision sensor from ground (inches)
  #define DISTANCE_SCALAR 1800 // scalar used to calculate distance to cap

  // signatures
  #define CAP_SIG_RED 1
  #define CAP_SIG_BLUE 2

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
  } cap;

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