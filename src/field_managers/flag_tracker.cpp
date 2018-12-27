#include "../../include/field_managers/flag_tracker.hpp"
#include <cmath>

namespace flag_tracker {


  static const Flag FLAG_NONE = {false};


  // config
  #define SENSOR_ANGLE_RAD SENSOR_ANGLE * PI / 180


  // vision sensor
  pros::Vision vision_sensor(10);


  // color codes
  pros::vision_color_code_t code_red = vision_sensor.create_color_code(FLAG_SIG_RED, FLAG_SIG_GREEN);
  pros::vision_color_code_t code_blue = vision_sensor.create_color_code(FLAG_SIG_GREEN, FLAG_SIG_BLUE);


  // arrays of flags and flagpoles
  int flag_count = 0;
  Flag flags[MAX_FLAGS];
  Flagpole flagpoles[MAX_FLAGPOLES];


  // calculate distance from vision y coordinate
  float calc_flag_dist(float height, float center_y) {
      return sin(SENSOR_ANGLE_RAD) * (height - SENSOR_HEIGHT) * DISTANCE_SCALAR / (VISION_IMAGE_WIDTH/2 - center_y); // UNTESTED CALCULATION
  }


  float get_pole_location(Flag flag) {
    return (flag.color == color_red) ? flag.vision_x : flag.vision_x + flag.width;
  }


  // create flag object
  Flag create_flag(float vision_x, float vision_y, float width, float height, Color color) {
    Flag flag;
    flag.identified = true;
    flag.vision_x = vision_x;
    flag.vision_y = vision_y;
    flag.width = width;
    flag.height = height;
    flag.color = color;
    return flag;
  }


  // create flagpole object
  Flagpole create_flagpole(Flag flag_top, Flag flag_mid, Flag flag_btm) {
    Flagpole pole;

    if (flag_top.identified || flag_mid.identified || flag_btm.identified) {
      pole.identified = true;

      // calculate distance
      float dist_btm = (flag_btm.identified) ? calc_flag_dist(FLAG_HEIGHT_BTM, flag_btm.vision_y) : 0;
      float dist_mid = (flag_mid.identified) ? calc_flag_dist(FLAG_HEIGHT_MID, flag_mid.vision_y) : 0;
      float dist_top = (flag_top.identified) ? calc_flag_dist(FLAG_HEIGHT_TOP, flag_top.vision_y) : 0;
      int identified_count = flag_btm.identified + flag_mid.identified + flag_top.identified;
      pole.robot_dist = (dist_btm + dist_mid + dist_top) / identified_count;

      pole.robot_x = 1 * get_pole_location(flag_btm) / pole.robot_dist; // UNTESTED CALCULATION
      pole.flag_top = flag_top;
      pole.flag_mid = flag_mid;
      pole.flag_btm = flag_btm;
    }

    return pole;
  }


  // upate flag list
  void update_flags() {

    // "remove" all previously stored flags
    for (int i = 0; i < MAX_FLAGS; i++) {
      flags[i].identified = false;
    }

    // find new flags
    pros::vision_object_s_t flags_red_raw[MAX_FLAGS];
    pros::vision_object_s_t flags_blue_raw[MAX_FLAGS];
    int flag_count_red = vision_sensor.read_by_code(0, code_red, MAX_FLAGS, flags_red_raw);
    int flag_count_blue = vision_sensor.read_by_code(0, code_blue, MAX_FLAGS - ((flag_count_red == PROS_ERR) ? 0 : flag_count_red), flags_blue_raw);

    if (flag_count_red == PROS_ERR || flag_count_red < 1) flag_count_red = 0;
    if (flag_count_blue == PROS_ERR || flag_count_blue < 1) flag_count_blue = 0;
    flag_count = flag_count_red + flag_count_blue;

    if (flag_count != PROS_ERR && flag_count > 0) {

      // convert to Flag structs
      Flag flags_unsorted[flag_count];
      for (int i = 0; i < flag_count_red; i++) {
        flags_unsorted[i] = create_flag(flags_red_raw[i].left_coord, flags_red_raw[i].top_coord, flags_red_raw[i].width, flags_red_raw[i].height, color_red);
      }
      for (int i = 0; i < flag_count_blue; i++) {
        flags_unsorted[i] = create_flag(flags_blue_raw[i].left_coord, flags_blue_raw[i].top_coord, flags_blue_raw[i].width, flags_blue_raw[i].height, color_blue);
      }

      // sort by x coordinate and store in flags array
      for (int i = 0; i < flag_count; i++) {
        int min_index = 0;
        float min_x = flags_unsorted[0].vision_x;

        for (int j = 0; j < flag_count; j++) {
          if (flags_unsorted[min_index].identified == false || (flags_unsorted[j].identified && flags_unsorted[j].vision_x > min_x)) {
            min_index = j;
            min_x = flags_unsorted[j].vision_x;
          }
        }

        flags[i] = flags_unsorted[min_index];
        flags_unsorted[min_index].identified = false;
      }
    }
  }


  // update flagpole list
  void update_flagpoles() {
    
    // "remove" all previously stored flagpoles
    for (int i = 0; i < MAX_FLAGPOLES; i++) {
      flagpoles[i].identified = false;
    }
    int pole_index = 0;

    // make copy of flags array
    Flag flags_cpy[flag_count];
    for (int i = 0; i < flag_count; i++) flags_cpy[i] = flags[i];

    // loop through and find flags with same flagpole
    for (int i = 0; i < flag_count; i++) {
      if (pole_index < MAX_FLAGPOLES && flags_cpy[i].identified) {
        flags_cpy[i].identified = false;

        // calculate pole location
        float pole_location = get_pole_location(flags_cpy[i]);

        // create small array to store flags on pole
        Flag pole[3];
        pole[0] = flags_cpy[i];
        int pole_flags = 1;

        // find other flags on same pole
        for (int j = i; j < flag_count; j++) {
          if (pole_flags < 3 && fabs(get_pole_location(flags_cpy[j]) - pole_location) <= SAME_POLE_BUFFER) {
            pole[pole_flags] = flags_cpy[j];
            pole_flags++;
            flags_cpy[j].identified = false;
          }
        }

        // sort flags (lowest -> highest)
        Flag pole_sorted[pole_flags];
        for (int j = 0; j < pole_flags; j++) {
          int min_index = 0;
          float min_height = pole[0].vision_y;

          for (int k = 0; k < pole_flags; k++) {
            if (pole[min_index].identified == false || (pole[k].identified && pole[k].vision_y < min_height)) {
              min_index = k;
              min_height = pole[k].vision_y;
            }
          }

          pole_sorted[j] = pole[min_index];
          pole[min_index].identified = false;
        }


        // put flags onto flagpole object
        flagpoles[pole_index] = create_flagpole(
          (pole_flags >= 3) ? pole_sorted[2] : FLAG_NONE,
          (pole_flags >= 2) ? pole_sorted[1] : FLAG_NONE,
          (pole_flags >= 1) ? pole_sorted[0] : FLAG_NONE
        );

        pole_index++;
      }
    }
  }
}
