#include "StateMachine.h"

static int current_floor; 

//kan ikke være mellom etg 
//må kjøres relativt ofte for å kunne få med seg at etasjen skal/har skiftet
void sm_set_current_floor_and_indicator(){
	if (elev_get_floor_sensor_signal() != NOT_ON_FLOOR){
		current_floor = elev_get_floor_sensor_signal();
		elev_set_floor_indicator(sm_get_current_floor()); 
	}
}

int sm_get_current_floor(){
	return current_floor; 
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

//åpner døren i 3 sekunder og så lukker døren 
void sm_door_handler(){
	elev_set_door_open_lamp(1); 
	sm_timer_handler(); 
	elev_set_door_open_lamp(0); 
}

void sm_order_in_Q_vs_current_floor(){
	if(qm_if_order_in_Q_at_current_floor(current_floor)){
		//setter motor dir til STOP
		mm_set_motor_dir(DIRN_STOP); 
		qm_delete_executed_order(current_floor);
		sm_turn_lights_off_in_floor(current_floor);
	}
}

//skal skur av lyset på knapper når vi skal sletter bestillinen ??
void sm_turn_lights_off_in_floor(int order_on_floor){
	//HVOR VAR DET I DEN GAMLE KODEN VI SKRUDDE AV LYSET NÅR EN BESTILING VAR FERDIG
	//qm_delete_executed_order(order_on_floor); 
	//skru av lyset i elev 
	elev_set_button_lamp(BUTTON_CALL_UP, order_on_floor, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, order_on_floor, 0);
	elev_set_button_lamp(BUTTON_COMMAND, order_on_floor, 0);
} 

void sm_check_stop_button(){
	if (elev_get_stop_signal() == 1) {
		sm_stop_button_activated_ignore_orders();
	}
}

//stopp knapp aktivert
void sm_stop_button_activated_ignore_orders(){
	//skruer på stopp lampen 
	elev_set_stop_lamp(1);
	//stopper motoren 
	elev_set_motor_direction(DIRN_STOP);
	//sletter køen 
	qm_delete_Q();
	sm_reset_all_button_lamps_delete_Q();
	//heisen står mellom to etg 	
	if (elev_get_floor_sensor_signal() == -1) {

		while (elev_get_stop_signal() == 1) {
			continue;
		}
		elev_set_stop_lamp(0); 
	}
	else {
		//stopp knappen ble aktivert når vi er en etg 
		elev_set_door_open_lamp(1);
		while (elev_get_stop_signal() == 1) {
			continue;
		}
		elev_set_stop_lamp(0); 
		//døren er åpen i tre sekunder etter at vi har sluppet stop knappen men vi kan ta i mot ordere 
		sm_timer_handler(); 
		elev_set_door_open_lamp(0);
	} 
}

void sm_reset_all_button_lamps_delete_Q(){
	qm_delete_Q(); 

	int i;
    // Zero all floor button lamps
    for (i = 0; i < N_FLOORS; ++i) { // burde henne ha hver implimentert i++ 
        if (i != 0)
            elev_set_button_lamp(BUTTON_CALL_DOWN, i, 0);

        if (i != N_FLOORS - 1)
            elev_set_button_lamp(BUTTON_CALL_UP, i, 0);

        elev_set_button_lamp(BUTTON_COMMAND, i, 0);
    }
}

int sm_elev_on_standby(){
	if (qm_is_Q_empty() == 1){
		//sette motoren til å stoppe
		mm_set_motor_dir(DIRN_STOP); 
		return 1;
	}
	else{
		return 0; 
	}
}

void sm_elev_move_or_stop(){
	
	if (sm_elev_on_standby()) {	
		printf("Det er ikke noe i Q\n");}
	else {
		if (elev_get_floor_sensor_signal() != -1) {
			sm_drive_direction();
		}
		else {}
	}
}

void sm_drive_direction(){

	int last_driving_dir = mm_get_last_moving_motor_dir();

	switch(last_driving_dir) {

		case(DIRN_DOWN):
			case_dirn_down();
			break;

		case(DIRN_UP):
			case_dirn_up();
			break; 

		default:
			printf("kom hit \n");
		}
}

void case_dirn_up() {
	int floor = elev_get_floor_sensor_signal(); 

	if (floor != -1){
		int smth_in_Q_over = 0;

		printf("case DIRN_UP\n");
		for (int j = floor; j < 4; j++){
			if (qm_get_order_in_Q_up(j) || qm_get_order_in_Q_down(j) || qm_get_order_in_Q_command(j)) {
				printf("funnet en order over \n");
				mm_set_motor_dir(DIRN_UP);
				//mm_set_last_moving_motor_dir(DIRN_UP);
				smth_in_Q_over = 1;
				break;
			}
		}
		if (smth_in_Q_over == 0){
			printf("Er ingen bestilling over, KJØR NED\n");
			mm_set_motor_dir(DIRN_DOWN);
			mm_set_last_moving_motor_dir(DIRN_DOWN);
		}
	}
	else {}
}

void case_dirn_down(){
	int floor = elev_get_floor_sensor_signal(); 

	if (floor != -1){
		int smth_in_Q_under = 0;

		for (int i = floor ; i > -1; i--){
			if (qm_get_order_in_Q_up(i) || qm_get_order_in_Q_down(i) || qm_get_order_in_Q_command(i)) {
				printf("funnet en order under \n");
				mm_set_motor_dir(DIRN_DOWN);
				//mm_set_last_moving_motor_dir(DIRN_DOWN);
				smth_in_Q_under = 1;
				break;
			}
		}
		
		if (smth_in_Q_under == 0) {
			//vet vi skal oppover 
			printf("Er ingen bestilling under. vi kjører opp\n" );
			mm_set_motor_dir(DIRN_UP);
			mm_set_last_moving_motor_dir(DIRN_UP);
		}
	}
	else{}
}
