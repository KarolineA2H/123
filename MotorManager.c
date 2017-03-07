#include "MotorManager.h"
#include "elve.h"

void mm_set_motor_dir (int motor_direction){
	motor_dir= motor_direction; 
	elev_set_motor_direction(motor_dir); //skal vi gjøre dette her. eller er det ikke vits? 
}
int mm_get_motot_dir(){
	return motor_dir; 
} 


void mm_set_last_moving_motor_dir(int motor_direction){
	if (motor_dir != -1)
	last_moving_motor_dir= motor_direction; 
} 
int mm_get_last_moving_motor_dir(){
	return last_moving_motor_dir; 
}