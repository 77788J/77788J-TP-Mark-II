#ifndef MACROS_H_
#define MACROS_H_

#include "subsystems/subsystems.hpp"

namespace macros {

  // current macro
  enum Macro {MACRO_NONE, MACRO_STACK, MACRO_RESET_CATAPULT};
  extern Macro current_macro;

  // task
  void update(void* param);

  // stack cap
  void stack();
  void reset_catapult();

}

#endif