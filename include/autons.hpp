#ifndef AUTONS_H_
#define AUTONS_H_

namespace autons {

  static const bool SKILLS = false;
  static const bool WAIT = false;

  // variables
  extern void (*selected)(bool);
  extern bool park;

  // functions
  void auto_red_flag(bool park);
  void auto_blue_flag(bool park);
  void auto_red_flag_wait(bool park);
  void auto_blue_flag_wait(bool park);
  void auto_red_cap_park(bool park);
  void auto_red_cap_full(bool park);
  void auto_blue_cap_park(bool park);
  void auto_blue_cap_full(bool park);
  void auto_skills(bool park);

}

#endif