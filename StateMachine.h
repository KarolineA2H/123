#ifndef StateMachine
#define StateMachine
#include <stdio.h>

#include "Timer.h"
#include "elev.h"
#include "Qmanager.h"
#include "Initialize.h"
#include "MotorManager.h"

enum Floor{
	GROUND_FLOOR = 0,
	FIRST = 1,
	SECOND = 2,
	TOP_FLOOR = 3,
	NOT_ON_FLOOR = -1 //The elevator is between two floors  
};

/*
Sets the static variable current_floor and previous_floor to value returned from elev_get_floor_sensor_signal(). 
Also turns on the floor indicator lamp.
*/
void sm_set_current_floor_and_indicator();

/*
Returns the static variable current_floor.
*/
int sm_get_current_floor(); 

/*
Returns the static variable previous_floor.
*/
int sm_get_previous_floor();

/*
Checks if a BUTTON_CALL_UP button is pressed. 
If pressed, sets corresponding element in array to 1. 
*/
void sm_check_button_pressed_up(); 

/*
Checks if a BUTTON_CALL_DOWN button is pressed. 
If pressed, sets corresponding element in array to 1. 
*/
void sm_check_button_pressed_down(); 

/*
Checks if a BUTTON_COMMAND button is pressed. 
If pressed, sets corresponding element in array to 1. 
*/
void sm_check_button_pressed_command(); 

/*
Checks all buttons, excluding the stop-button.
Runs the three above functions.
*/
void sm_check_button_pressed(); 

/*
Handles everything about the timer. 
Also checks all buttons while checking the timer.
*/
void sm_timer_handler(); 

/*
Handles the door.
Sets the door lamp to on, counts down 3 seconds and turns the door lamp off. 
*/  
void sm_door_handler(); 

/*
Checks if the elevator has an order at the floor it is at. 
*/
void sm_order_in_Q_vs_current_floor();

/*
Checks the command-queue for an order at the floor it is at. 
Returns 1 if there is an order, 0 if not.
*/
int sm_check_Q_command_for_orders();

/*
Checks the down-queue for an order at the floor it is at. 
Returns 1 if there is an order, 0 if not.
*/
int sm_check_Q_down_for_orders();

/*
Checks the up-queue for an order at the floor it is at. 
Returns 1 if there is an order, 0 if not.
*/
int sm_check_Q_up_for_orders();

/*
Handles the process of stopping at a floor.
Sets motor direction to DIRN_STOP, deletes the order, and turns lights off.
*/
void sm_when_stopping_at_floor();

/*
Turns the lights for BUTTON_CALL_UP, BUTTON_CALL_DOWN and BUTTON_COMMAND off at floor indicated by 'order_on_floor'
*/
void sm_turn_lights_off_in_floor(int order_on_floor); 

/*
Checks if the stop-button is activated. 
*/
void sm_check_stop_button();

/*
Handles if the stop-button is activated.
*/
void sm_stop_button_activated_ignore_orders(); 

/*
Deletes all orders in the queues and turns all lights for BUTTON_CALL_UP, BUTTON_CALL_DOWN and BUTTON_COMMAND buttons off.
*/
void sm_reset_all_button_lamps_delete_Q(); 

/*
Checks if the queues are empty. If they are, returns 1. If not, returns 0.
*/
int sm_elev_on_standby(); 

/*
Decides motor direction. 
If the elevator is on standby, the motor direction is 0. If not, this function decides which direction to go.
*/
void sm_elev_move_or_stop();

/*
Checks which direction last moving direction was and runs either case_dirn_up() or case_dirn_down()
*/
void sm_drive_direction();

/*
Runs if last moving motor direction was DIRN_UP, decides which direction to start again.
*/
void case_dirn_up();

/*
Runs if last moving motor direction was DIRN_DOWN, decides which direction to start again.
*/
void case_dirn_down();

/*
Checks which direction last moving direction was and run either case_dirn_up_between_floors() or case_dirn_down_between_floors()
Runs after the stop-button has been activated and the elevator is between floors.
*/
void sm_drive_direction_between_floors();

/*
Runs if last moving motor direction was DIRN_UP, decides which direction to start again when he elevator is between floors.
*/
void case_dirn_up_between_floors();

/*
Runs if last moving motor direction was DIRN_DOWN, decides which direction to start again when he elevator is between floors.
*/
void case_dirn_down_between_floors();

#endif
