#include "../../include/lib/analog_switch.hpp"

// initializer
AnalogSwitch::AnalogSwitch(char port, int _engage_threshold, int _disengage_threshold, float _filter_strength):

  // initialie sensor
  sensor(pros::ADIAnalogIn(port)),

  // initialize variable values
  acticated(false),
  activated_new(0),
  engage_threshold(_engage_threshold),
  disengage_threshold(_disengage_threshold),
  filter_strength(_filter_strength) {}


// update reading
void AnalogSwitch::update() {

  // temporary variable to store current value
  float value = (float)prev_value * filter_strength + sensor.get_value() * (1 - filter_strength);
  bool p = acticated ? value > disengage_threshold : value > engage_threshold;

  // determine new press
  activated_new = p - acticated;

  // save currently pressed permanently
  acticated = p;

  // save new previous value
  prev_value = value;
}