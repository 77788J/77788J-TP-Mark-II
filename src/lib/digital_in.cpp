#include "../../include/lib/digital_in.hpp"


// initializer
DigitalIn::DigitalIn(char port):

  // initialize sensor object
  sensor(pros::ADIDigitalIn(port)), 
  
  // set default values
  pressed(false), 
  pressed_new(0) {};


// updte reading
void DigitalIn::update() {

  // temporary variable to store current value
  bool p = !sensor.get_value(); // by default HIGH is true and LOW is false- we want this swapped

  // determine new press
  pressed_new = p - pressed;

  // save currently pressed permanently
  pressed = p;
}