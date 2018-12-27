#ifndef FLAG_TRACKER_H_
#define FLAG_TRACKER_H_

#include "../main.h"

namespace flag_tracker {

  // config
  static const int MAX_FLAGS = 9; // maximum amount of flags to look for
  static const int MAX_FLAGPOLES = 3; // maximum amount of flagpoles to hold
  static const float SENSOR_ANGLE = -60; // angle of vision sensor (degrees)
  static const float SENSOR_HEIGHT = 12; // height of vision sensor from ground (inches)
  static const float DISTANCE_SCALAR = 1800; // scalar used to calculate distance to flag
  static const float SAME_POLE_BUFFER = 40; // maximum number of pixels apart flags can be to be considered on the same pole

  // flag heights
  static const float FLAG_HEIGHT_TOP = 46.3; // height of top flags (inches)
  static const float FLAG_HEIGHT_MID = 32.4; // height of middle flags (inches)
  static const float FLAG_HEIGHT_BTM = 18.3; // height of bbottom flags (inches)

  // signatures
  static const int FLAG_SIG_RED = 1;
  static const int FLAG_SIG_BLUE = 2;
  static const int FLAG_SIG_GREEN = 3;

  // possible flag colors
  enum Color {color_red, color_blue};

  // stores all data of a flag
  typedef struct Flag {
    bool identified;
    float vision_x;
    float vision_y;
    float width;
    float height;
    Color color;
  } Flag;

  // stores all data of a flagpole
  typedef struct Flagpole {
      bool identified;
      float robot_x;
      float robot_dist;
      Flag flag_top;
      Flag flag_mid;
      Flag flag_btm;
  } Flagpole;

  // vision sensor
  extern pros::Vision vision_sensor;

  // arrays of flags and flagpoles
  extern int flag_count; // how many flags are currently visible
  extern Flag flags[MAX_FLAGS]; // array of flags currently visible
  extern Flagpole flagpoles[MAX_FLAGPOLES]; // array of flagspoles currently visible

  // calculate distance from vision y coordinate
  float calc_flag_dist(float height, float center_y);

  // create flag object
  Flag create_flag(float vision_x, float vision_y, float width, float height, Color color);

  // create flagpole object
  Flagpole create_flagpole(Flag flag_top, Flag flag_mid, Flag flag_btm);

  // upate flag list
  void update_flags();

  // update flagpole list
  void update_flagpoles();

}

#endif