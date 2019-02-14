#ifndef DIGITAL_IN_H_
#define DIGITAL_IN_H_

#include "../main.h"

class DigitalIn {

public:

  // sensor object
  pros::ADIDigitalIn sensor;

  // currently pressed
  bool pressed;

  // registers NEW presses
  char pressed_new;

  // initializer
  DigitalIn(char port);

  // update reading
  void update();

};

#endif