#include "../../include/main.h"
#include "../../include/autons.hpp"
#include "../../include/subsystems/subsystems.hpp"


void autonomous() {

  //                      PARK   RED    DO OTHER CRAP
  // autons::auto_cap_simple(true, true, true);

  chassis::rotate_to_orientation(270);
  
}
