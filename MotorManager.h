#ifndef MotorManager
#define MotorManager 

#include <stdio.h>



void mm_set_motor_dir (int motor_direction); 
int mm_get_motor_dir(); 


void mm_set_last_moving_motor_dir(int motor_direction); 
int mm_get_last_moving_motor_dir(); 



#endif