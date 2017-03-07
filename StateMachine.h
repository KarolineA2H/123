#ifndef StateMachine
#define StateMachine
#include <stdio.h>

#include "Timer.h"
#include "elev.h"
#include "QueueManager.h"
#include "Initialize.h"
#include "MotorManager.h"


int current_floor; 

enum Floor{
	GROUND_FLOOR = 0,
	FIRST = 1,
	SECOND = 2,
	TOP_FLOOR = 3,
	NOT_ON_FLOOR = -1//The elevator is between two floors  
};


void sm_set_current_floor(int floor_signal); //kan ikke være -1 (NOT_ON_FLOOR)
int sm_get_current_floor(); //trenger vi denne??

void sm_set_floor_indicator(int floor_signal); // setter lys på indikatoren 

//skjekker alle type bestillingsknapper
void sm_check_button_pressed_up(); 
void sm_check_button_pressed_down(); 
void sm_check_button_pressed_command(); 

void sm_check_button_pressed(); 

//teller ned tre sek og skjekker alle knapper
void sm_timer_handler(); 

//setter lyset på ved 1. Vis man vil ha døren åpen 
void sm_door_handler(int bool_value); 

//skal vi stoppe på denne etg. og sette motor retning til 0 
void sm_order_in_Q_vs_current_floor(int current_floor); 

//skal skur av lyset på knapper når vi skal sletter bestillingen
void sm_turn_lights_on_off_in_floor(int order_on_floor); 

//stopp knapp aktivert
void sm_stop_button_activated_ignore_orders(); 

//heisen står stille og venter på at den skal få et nytt oppdrag
int sm_elev_on_standby(); 





#endif