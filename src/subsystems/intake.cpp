#include "../../include/subsystems/intake.hpp"
#include "../../include/field_managers/ball_tracker.hpp"

namespace intake {

  // motor
  pros::Motor motor(12, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);


  // line switch
  AnalogSwitch line('B', 1200, 1800, .85);


  // state data
  int state = 0;
  Mode mode = MODE_OFF;


  // how many balls currently loaded
  char max_loaded = 2;
  char currently_loaded = 0;
  char max_in_catapult = 1;
  char in_catapult = 0;
  bool in_intake = false;


  // switch mode
  void set_mode(Mode new_mode) {
    if (mode != new_mode) {

      mode = new_mode;

      switch (mode) {
        case (MODE_OFF): state = 0; break;
        case (MODE_INTAKE): state = 1; break;
        case (MODE_OUTTAKE): state = -1; break;
        case (MODE_AUTO): break;
      }

      motor.move_voltage(state * 12000);
    }
  }


  // toggle on/off
  void toggle(Mode new_mode) { 
    if (new_mode == mode) set_mode(MODE_OFF);
    else set_mode(new_mode);
  }


  // reset ball stats
  void reset_balls() {
    currently_loaded = 0;
    in_catapult = 0;
  }


  // update
  int last_update = -1500;
  int last_in_intake = -500;
  void update(int delta_t) {
    line.update();

    // if (pros::millis() > 1000) {
    if (false) {
      if (!line.acticated) {
        in_intake = true;
        last_in_intake = pros::millis();
        printf("in intake\n");
      }
      else in_intake = false;
      if (line.activated_new == -1) {
        if (motor.get_voltage() > 0) ++in_catapult;
        else --currently_loaded;
      }
      if (line.activated_new == 1) ++currently_loaded;
    }

    if (mode == MODE_AUTO) {
      if ((in_intake && in_catapult >= max_in_catapult) || currently_loaded > max_in_catapult) motor.move_voltage(0);
      else if (
        ball_tracker::ball_count > 0 &&
        ball_tracker::vision_sensor.get_by_size(0).y_middle_coord > AUTO_Y_THRESHOLD &&
        ball_tracker::vision_sensor.get_by_size(0).width > 20 &&
        ball_tracker::vision_sensor.get_by_size(0).height > 20 &&
        currently_loaded < max_loaded
      ) {
        last_update = pros::millis();
        motor.move_voltage(12000);
      }
      else if (pros::millis() - last_update <= 2000 || pros::millis() - last_in_intake <= 500) motor.move_voltage(12000);
      else motor.move_voltage(0);

      printf("intake: %d\tcatapult: %d\n", currently_loaded, in_catapult);
    }
  }
}
