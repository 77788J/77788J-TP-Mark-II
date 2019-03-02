#ifndef AUTONS_H_
#define AUTONS_H_

namespace autons {

  static const bool SKILLS = true;

  // variables
  extern void (*selected)(bool);
  extern bool park;

  // functions
  void auto_red_flag(bool park);
  void auto_blue_flag(bool park);
  void auto_red_cap(bool park);
  void auto_skills(bool park);

}

#endif