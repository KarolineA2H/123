#ifndef MotorManager
#define MotorManager 

#include <stdio.h>

//er hvilken vei motoren har nå
static int motor_dir; 
//er vilken vei som motoren var satt til sist, når det var i bevegelse 
static int last_moving_motor_dir; 


void mm_set_motor_dir (int motor_direction); 
int mm_get_motor_dir(); 


void mm_set_last_moving_motor_dir(int motor_direction); 
int mm_get_last_moving_motor_dir(); 



#endif