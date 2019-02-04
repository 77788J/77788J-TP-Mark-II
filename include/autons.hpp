#ifndef AUTONS_H_
#define AUTONS_H_

namespace autons {

  // enum
  enum Auton {
    AUTON_NONE,
    AUTON_RED_FLAG,
    AUTON_RED_CAP,
    AUTON_BLUE_FLAG,
    AUTON_BLUE_CAP
  };

  // variables
  extern Auton selected;
  extern bool feed;
  extern bool park;

  // functions
  void auto_red_flag();
  void auto_blue_flag();
  void auto_red_cap();
  void auto_red_cap_feed();
  void auto_blue_cap();
  void auto_blue_cap_feed();

}

#endif