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
	NOT_ON_FLOOR = -1//The elevator is between two floors  
};


void sm_set_current_floor_and_indicator(); //kan ikke være -1 (NOT_ON_FLOOR)
int sm_get_current_floor(); 


int sm_get_previous_floor();


//skjekker alle type bestillingsknapper
void sm_check_button_pressed_up(); 
void sm_check_button_pressed_down(); 
void sm_check_button_pressed_command(); 

void sm_check_button_pressed(); 

//teller ned tre sek og skjekker alle knapper
void sm_timer_handler(); 

//setter lyset på ved 1. Vis man vil ha døren åpen 
//sammtidig som vi teller tre sek  
void sm_door_handler(); 

//skal vi stoppe på denne etg. og sette motor retning til 0 
void sm_order_in_Q_vs_current_floor();

int sm_check_Q_command_for_orders();
int sm_check_Q_down_for_orders();
int sm_check_Q_up_for_orders();

void sm_when_stopping_at_floor();

//skal skur av lyset på knapper når vi skal sletter bestillingen
void sm_turn_lights_off_in_floor(int order_on_floor); 

//sjekker og håndterer stoppknappen
void sm_check_stop_button();

//stopp knapp aktivert
void sm_stop_button_activated_ignore_orders(); 

//slukker alle bestillingsknapper og sletter køen 
void sm_reset_all_button_lamps_delete_Q(); 

//heisen står stille og venter på at den skal få et nytt oppdrag
int sm_elev_on_standby(); 

//ligger i main, bestemmer motor dir.
void sm_elev_move_or_stop();

// bestemmer motor state (UP/DOWN/STOP)
void sm_drive_direction();

void case_dirn_up();
void case_dirn_down();

void sm_drive_direction_between_floors();
void case_dirn_up_between_floors();
void case_dirn_down_between_floors();


#endif