/*
 * File:          factory_supervisor.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <webots/robot.h>
#include <webots/display.h>
#include <webots/supervisor.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

WbDeviceTag display;
const char *stateComplete = "Complete";
const char *stateBroken = "Broken";
const char *stateInProgress = " - ";
const char *stateIntact = "Intact";

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();

  display = wb_robot_get_device("display");
  wb_display_set_color(display, 0xFFFFFF);
  wb_display_set_font(display, "Arial", 16, true);

  WbNodeRef dropPoint[3];
  for (int i = 0; i < 3; i++) {
    char *defName[] = {
      "DropPointL1",
      "DropPointL2",
      "DropPointL3",
    };
    dropPoint[i] = wb_supervisor_node_get_from_def(defName[i]);
    if (dropPoint[i] == NULL) {
      printf("%s : NULL\n", defName[i]);
    }
  }
  WbNodeRef crate[3];
  for (int i = 0; i < 3; i++) {
    char *defName[] = {"Crate1", "Crate2","Crate3"};
    crate[i] = wb_supervisor_node_get_from_def(defName[i]); 
    if (crate[i] == NULL)
      printf("%s : NULL\n", defName[i]);
  }

  /* get the time step of the current world. */
  const int time_step = (int) wb_robot_get_basic_time_step();

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
  const char *crateState[3] = {stateIntact, stateIntact, stateIntact};
  const char *dropState[3] = {stateInProgress, stateInProgress, stateInProgress};
  const char *finalState[3] = {stateInProgress, stateInProgress, stateInProgress};
  const double *cratePos[3];  // 荷物の現在位置
  const double *dropPos[3];   // 設置位置
  double dropTime[3];
  /* main loop
   * Perform simulation steps of the current world's basic time step
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(time_step) != -1) {
    // clear
    wb_display_set_color(display, 0xFFFFFF);
    wb_display_fill_rectangle(display, 0, 0, 256, 256);
    wb_display_set_color(display, 0);
    // 配達完了フラグチェック
    for (int i = 0; i < 3; i++) {
      WbFieldRef customData =
          wb_supervisor_node_get_field(crate[i], "status");
      if (customData == NULL) {
        printf("Crate%d:NULL\n", i);
      } 
      const char *state = 
          wb_supervisor_field_get_sf_string(customData);
      if (strcmp(state, "broken") == 0) {
        crateState[i] = stateBroken;
      }
      printf("######## crateState[%d]:%s\n", i, crateState[i]);
      WbFieldRef translation = wb_supervisor_node_get_field(crate[i], "translation");
      cratePos[i] = wb_supervisor_field_get_sf_vec3f(translation);

      customData =
          wb_supervisor_node_get_field(dropPoint[i], "contactState");
      if (customData == NULL) {
        printf("DropPoint%d:NULL\n", i);
      } 
      state =
          wb_supervisor_field_get_sf_string(customData);
      if (strcmp(state, "1") == 0 && dropState[i] == stateInProgress) {
        dropState[i] = stateComplete;
        dropTime[i] = wb_robot_get_time();
      }
      printf("######## dropState[%d]:%s %s\n", i, dropState[i], state);
      translation = wb_supervisor_node_get_field(dropPoint[i], "translation");
      dropPos[i] = wb_supervisor_field_get_sf_vec3f(translation);
    }
    for (int i = 0; i < 3; i++) {
      char buff[32];

      if (dropState[i] == stateComplete && finalState[i] == stateInProgress) {
        for (int j = 0; j < 3; j++) {
          printf("%d:%d = %f\n", i,j,powf(dropPos[i][0] - cratePos[j][0], 2.0) + powf(dropPos[i][1] - cratePos[j][1], 2.0));
          if (powf(dropPos[i][0] - cratePos[j][0], 2.0) + powf(dropPos[i][1] - cratePos[j][1], 2.0) < 4.0) {
            if (crateState[j] == stateBroken) {
              finalState[i] = stateBroken;
            } else {
              finalState[i] = stateComplete;
            }
            break;
          }
        }
      }

      sprintf(buff, "Drop%d:%s %d'%02.2f", i, finalState[i], (int)(dropTime[i]/60), dropTime[i] - floorf(dropTime[i]/60)*60);
      wb_display_draw_text(display, buff, 0, i*24);
    }

    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
