#ifndef MotorManager
#define MotorManager 

#include <stdio.h>

/*
Sets static variable motor_dir to int passed to function.
*/
void mm_set_motor_dir (int motor_direction); 

/*
Returns static variable motor_dir
*/
int mm_get_motor_dir(); 

/*
Sets static variable last_moving_motor_dir to int passed to function
*/
void mm_set_last_moving_motor_dir(int motor_direction);

/*
Returns static variable last_moving_motor_dir
*/
int mm_get_last_moving_motor_dir(); 

#endif
