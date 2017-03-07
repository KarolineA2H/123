#include "StateMachine.h"

int current_floor; 

enum Floor{
	GROUND_FLOOR = 0,
	FIRST = 1,
	SECOND = 2,
	TOP_FLOOR = 3,
	NOT_ON_FLOOR = -1//The elevator is between two floors  
};


//kan ikke være mellom etg 
void sm_set_current_floor(int floor_signal){
	if (elev_get_floor_sensor_signal() != NOT_ON_FLOOR){
	current_floor = elev_get_floor_sensor_signal();
	}	
}
int sm_get_current_floor(){
	return current_floor; 
}

void sm_set_floor_indicator(int floor_signal){
	///HVA SKAL DET VÆRE HER? 
}


//sjekker om en knapp er trykket og 
//legger til i kø og setter på lys, hvis en er trykket
void sm_check_button_pressed_up(){
	qm_set_order_in_Q_up(TOP_FLOOR, 0); // denne knappen finnes ikke fysisk 

	if (elev_get_button_signal(BUTTON_CALL_UP, GROUND_FLOOR) == 1) {
		qm_set_order_in_Q_up(GROUND_FLOOR, 1);
		elev_set_button_lamp(BUTTON_CALL_UP, GROUND_FLOOR, 1);
	}
	if (elev_get_button_signal(BUTTON_CALL_UP, FIRST) == 1) {
		qm_set_order_in_Q_up(FIRST, 1);
		elev_set_button_lamp(BUTTON_CALL_UP, FIRST, 1);
	}
	if (elev_get_button_signal(BUTTON_CALL_UP, SECOND) == 1) {
		qm_set_order_in_Q_up(SECOND, 1);
		elev_set_button_lamp(BUTTON_CALL_UP, SECOND, 1);
	}

}
void sm_check_button_pressed_down(){
	qm_set_order_in_Q_down(GROUND_FLOOR, 0);

	if (elev_get_button_signal(BUTTON_CALL_DOWN, FIRST) == 1) {
		qm_set_order_in_Q_down(FIRST, 1);
		elev_set_button_lamp(BUTTON_CALL_DOWN, FIRST, 1);
	} 
	if (elev_get_button_signal(BUTTON_CALL_DOWN, SECOND) == 1) {
		qm_set_order_in_Q_down(SECOND, 1);
		elev_set_button_lamp(BUTTON_CALL_DOWN, SECOND, 1);
	} 
	if (elev_get_button_signal(BUTTON_CALL_DOWN, TOP_FLOOR) == 1) {
		qm_set_order_in_Q_down(TOP_FLOOR, 1);
		elev_set_button_lamp(BUTTON_CALL_DOWN, TOP_FLOOR, 1);
	}
}

void sm_check_button_pressed_command(){
	if (elev_get_button_signal(BUTTON_COMMAND, GROUND_FLOOR) == 1) {
		qm_set_order_in_Q_command(GROUND_FLOOR, 1);
		elev_set_button_lamp(BUTTON_COMMAND, GROUND_FLOOR, 1);
	}
	if (elev_get_button_signal(BUTTON_COMMAND, FIRST) == 1) {
		qm_set_order_in_Q_command(FIRST, 1);
		elev_set_button_lamp(BUTTON_COMMAND, FIRST, 1);
	}
	if (elev_get_button_signal(BUTTON_COMMAND, SECOND) == 1) {
		qm_set_order_in_Q_command(SECOND, 1);
		elev_set_button_lamp(BUTTON_COMMAND, SECOND, 1);
	}
	if (elev_get_button_signal(BUTTON_COMMAND, TOP_FLOOR) == 1) {
		qm_set_order_in_Q_command(TOP_FLOOR, 1);
		elev_set_button_lamp(BUTTON_COMMAND, TOP_FLOOR, 1);
	}
}

//skjekker alle type bestillingsknapper og setter lyset 
void sm_check_button_pressed(){
	sm_check_button_pressed_up(); 
	sm_check_button_pressed_down(); 
	sm_check_button_pressed_command(); 
} 

//teller tre sek. men skjekker også knappene+
void sm_timer_handler(){
	t_start_timer(); 
	//så lenge vi teller ned tre sekunder 
	while(t_check_timer()!= 1){
		sm_check_button_pressed(); 
	}
}

//setter lyset på ved 1. Vis man vil ha døren åpen 
void sm_door_handler(int bool_value){
	elev_set_door_open_lamp(bool_value); 
}

//skal vi stoppe på denne etg. og sette motor retning til 0 
void sm_order_in_Q_vs_current_floor(int current_floor){
	if(qm_check_current_order_floor_and_ord(current_floor)){
		//setter motor dir til STOP
		mm_set_motor_dir(DIRN_STOP); 
	}
}

//skal skur av lyset på knapper når vi skal sletter bestillinen ??
void sm_turn_lights_off_in_floor(int order_on_floor){
	//HVOR VAR DET I DEN GAMLE KODEN VI SKRUDDE AV LYSET NÅR EN BESTILING VAR FERDIG
	qm_delete_executed_order(order_on_floor); 
} 

//stopp knapp aktivert
void sm_stop_button_activated_ignore_orders(){
	//skruer på stopp lampen 
	elev_set_stop_lamp(1);
	//stopper motoren 
	elev_set_motor_direction(DIRN_STOP);
	//sletter køen 
	qm_delete_Q();
	//heisen står mellom to etg 	
	if (elev_get_floor_sensor_signal()== -1) {
		sm_door_handler(0); // sikrer seg at døren ikke er åpen 
		while (elev_get_stop_signal() == 1) {
			continue;
		}
	}
	else {
		//stopp knappen ble aktivert når vi er en etg 
		elev_set_door_open_lamp(1);
		while (elev_get_stop_signal() == 1) {
			continue;
		}
		//døren er åpen i tre sekunder etter at vi har sluppet stop knappen 
		sm_timer_handler(); 
	} 
	elev_set_stop_lamp(0); 
}

int sm_elev_on_standby(){
	if (qm_if_Q_is_empty()){
		return 1; 
	}
	else{
		printf("%s\n", "Køen er ikke tom" );
		return 0; 
	}
}

