#include "../../include/main.h"
#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"


void autonomous() {

  catapult::set_resting_position(catapult::resting_position);
  lift::goto_height(lift::HEIGHT_MIN);
  autons::selected(autons::park);
  
}
