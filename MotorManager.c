#include "MotorManager.h"
#include "elev.h"

void mm_set_motor_dir (int motor_direction){
	motor_dir= motor_direction; 
	elev_set_motor_direction(motor_dir); 
}

int mm_get_motor_dir(){
	return motor_dir; 
} 

void mm_set_last_moving_motor_dir(int motor_direction){
	if (motor_dir != 0){
		last_moving_motor_dir= motor_direction; 
	}
} 

int mm_get_last_moving_motor_dir(){
	return last_moving_motor_dir; 
}
