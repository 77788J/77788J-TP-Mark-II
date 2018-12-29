#ifndef INTAKE_H_
#define INTAKE_H_

#include "../main.h"

namespace intake {

  // auto intake distance threshold
  static const float auto_dist_threshold = 6;

  // intake modes
  enum Mode {
    MODE_OFF = 0,
    MODE_INTAKE = 1,
    MODE_OUTTAKE = -1,
    MODE_AUTO = 2
  };

  // motor
  extern pros::Motor motor;

  // mode
  extern Mode mode;

  // switch mode
  void set_mode(Mode new_mode);

  // toggle on/off
  void toggle(Mode new_mode);

  // update
  void update(int delta_t);

}

#endif