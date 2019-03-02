#ifndef DIGITAL_IN_H_
#define DIGITAL_IN_H_

#include "../main.h"

class AnalogSwitch {

public:

  // sensor object
  pros::ADIAnalogIn sensor;

  // currently pressed
  bool acticated;

  // registers NEW presses
  int activated_new;

  // previous value
  float prev_value;

  // filter strength
  float filter_strength;

  // activation threshold
  float engage_threshold;
  float disengage_threshold;

  // initializer
  AnalogSwitch(char port, int engage_threshold=1548, int disengage_threshold=1648, float filter_strength=.5);

  // update reading
  void update();

};

#endif