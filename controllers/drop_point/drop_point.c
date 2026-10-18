/*
 * File:          drop_point.c
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
#include <webots/touch_sensor.h>
#include <stdio.h>

WbDeviceTag touchSensor;

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  int count = 0;
  /* necessary to initialize webots stuff */
  wb_robot_init();

  /* get the time step of the current world. */
  const int time_step = (int) wb_robot_get_basic_time_step();

  touchSensor = wb_robot_get_device("touchSensor");
  wb_touch_sensor_enable(touchSensor, time_step);
  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
  printf("touchSensor start\n");
  wb_robot_set_custom_data("0");

  /* main loop
   * Perform simulation steps of the current world's basic time step
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(time_step) != -1) {
    double val = wb_touch_sensor_get_value(touchSensor);
    if (val > 0.5) {
      count++;
      if (count > 1000/time_step) {
        wb_robot_set_custom_data("1");
      }
    } else {
      count = 0;
    }
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
