#include "StateMachine.h"

static int current_floor; 
static int previous_floor;  
static int stop_button_pressed;


void sm_set_current_floor_and_indicator(){
	int floor = elev_get_floor_sensor_signal();

	if (floor != NOT_ON_FLOOR){
		current_floor = floor;
		elev_set_floor_indicator(current_floor); 
		previous_floor = current_floor; 
	}
}

int sm_get_current_floor(){
	return current_floor; 
}

int sm_get_previous_floor(){
	return previous_floor; 
}


void sm_check_button_pressed_up(){
	qm_set_order_in_Q_up(TOP_FLOOR, 0); // Not a physical button 

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
	qm_set_order_in_Q_down(GROUND_FLOOR, 0); // Not a physical button

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


void sm_check_button_pressed(){
	sm_check_button_pressed_up(); 
	sm_check_button_pressed_down(); 
	sm_check_button_pressed_command(); 
} 


void sm_timer_handler(){
	t_start_timer(); 
	while(t_check_timer()!= 1){
		sm_check_button_pressed(); 
	}
}

 
void sm_door_handler(){
	elev_set_door_open_lamp(1); 
	sm_timer_handler(); 
	elev_set_door_open_lamp(0); 
}

void sm_order_in_Q_vs_current_floor(){
	int floor = elev_get_floor_sensor_signal();
	// If the elevator is at a floor 
	if (floor != -1) {
		// Check if there is an order in any of the queues at the current floor and motor direction is DIRN_UP
		if((qm_get_order_in_Q_up(current_floor) || qm_get_order_in_Q_command(current_floor)) && mm_get_motor_dir() == DIRN_UP) {
			sm_when_stopping_at_floor();
		}
		// Check if there is an order in any of the queues at the current floor and motor direction is DIRN_DOWN
		if((qm_get_order_in_Q_down(current_floor) || qm_get_order_in_Q_command(current_floor)) && mm_get_motor_dir() == DIRN_DOWN ) {
			sm_when_stopping_at_floor();
		}

		// If there are no orders for going further up, check the down queue for orders at current floor
		if(sm_check_Q_up_for_orders() == 0 && sm_check_Q_command_for_orders() == 0) { 
			if (qm_get_order_in_Q_down(floor) == 1) {
				sm_when_stopping_at_floor();
			}
		}
		// If there are no orders for going further down, check the up queue for orders at current floor
		if(sm_check_Q_down_for_orders()== 0 && sm_check_Q_command_for_orders() == 0) { 
			if (qm_get_order_in_Q_up(floor) == 1) {
				sm_when_stopping_at_floor();
			}
		}
	}
}

int sm_check_Q_command_for_orders(){
	if (mm_get_motor_dir() == -1){
		for (int i = current_floor; i > -1; i--) {
			if (qm_get_order_in_Q_command(i) == 1) {
				return 1;
			}
		}
	}
	if (mm_get_motor_dir() == 1) {
		for (int i = current_floor; i < 4; i++) {
			if (qm_get_order_in_Q_command(i) == 1) {
				return 1;
			}
		}
	}
	return 0;
}

int sm_check_Q_down_for_orders(){
	for (int i = current_floor; i > -1; i--) {
		if (qm_get_order_in_Q_down(i) == 1) {
			return 1;
		}
	}
	return 0;
}


int sm_check_Q_up_for_orders(){
	for (int i = current_floor; i < 4; i++) {
		if (qm_get_order_in_Q_up(i) == 1) {
			return 1;
		}
	}
	return 0;
}

void sm_when_stopping_at_floor() {
	mm_set_motor_dir(DIRN_STOP); 
	qm_delete_executed_order(current_floor);
	sm_turn_lights_off_in_floor(current_floor);
	sm_door_handler();
}

void sm_turn_lights_off_in_floor(int order_on_floor){
	if (order_on_floor != 0) {
		elev_set_button_lamp(BUTTON_CALL_DOWN, order_on_floor, 0);
	}
	if (order_on_floor != 3){
		elev_set_button_lamp(BUTTON_CALL_UP, order_on_floor, 0);
	}	
	elev_set_button_lamp(BUTTON_COMMAND, order_on_floor, 0);
}

void sm_check_stop_button(){
	if (elev_get_stop_signal() == 1) {
		stop_button_pressed = 1;
		sm_stop_button_activated_ignore_orders();
	}
}

void sm_stop_button_activated_ignore_orders(){ 
	elev_set_stop_lamp(1); //Turn the stop-button lamp on 
	elev_set_motor_direction(DIRN_STOP);
	sm_reset_all_button_lamps_delete_Q();
	
	if (elev_get_floor_sensor_signal() == -1) {

		while (elev_get_stop_signal() == 1) {
			continue;
		}
		elev_set_stop_lamp(0); 
	}
	else {
		elev_set_door_open_lamp(1); 
		while (elev_get_stop_signal() == 1) {
			continue;
		}
		elev_set_stop_lamp(0); //Turn the stop-button off 
		sm_timer_handler(); //Count three seconds and simultaneously check the ordering buttons 
		elev_set_door_open_lamp(0); //Turn the door lamp off
	} 
}

void sm_reset_all_button_lamps_delete_Q(){
	qm_delete_Q(); 

	int i;
    for (i = 0; i < N_FLOORS; i++) { 
        if (i != 0)
            elev_set_button_lamp(BUTTON_CALL_DOWN, i, 0);

        if (i != N_FLOORS - 1)
            elev_set_button_lamp(BUTTON_CALL_UP, i, 0);

        elev_set_button_lamp(BUTTON_COMMAND, i, 0);
    }
}

int sm_elev_on_standby(){
	if (qm_is_Q_empty() == 1){
		mm_set_motor_dir(DIRN_STOP); 
		return 1;
	}
	else{
		return 0; 
	}
}

void sm_elev_move_or_stop(){
	if (sm_elev_on_standby()) {} // The Q is empty and the motor direction = DRIN STOP

	else {
		if (elev_get_floor_sensor_signal() != -1) { // If the elevator is at a floor 
			sm_drive_direction();
		}
		else if(stop_button_pressed == 1){ //If the elevator is between to floors, and the stop button has been activated 
			int DIR = mm_get_last_moving_motor_dir();

			if(DIR == DIRN_UP ){
				//Check if the first order is to a floor where the elevator just passed 
				if (qm_get_order_in_Q_up(previous_floor) || qm_get_order_in_Q_down(previous_floor) || qm_get_order_in_Q_command(previous_floor)){
					mm_set_motor_dir(DIRN_DOWN);
					mm_set_last_moving_motor_dir(DIRN_DOWN);
				}
				else{
					sm_drive_direction_between_floors();
				}
			}
			else if(DIR == DIRN_DOWN){
				//Check if the first order is to a floor where the elevator just passed
				if (qm_get_order_in_Q_up(previous_floor) || qm_get_order_in_Q_down(previous_floor) || qm_get_order_in_Q_command(previous_floor)){
					mm_set_motor_dir(DIRN_UP);
					mm_set_last_moving_motor_dir(DIRN_UP);
				}
				else {	
					sm_drive_direction_between_floors();
				}
			}
			//The stop-button case is handeled
			stop_button_pressed = 0;
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
			printf("Default last moving motor dir \n");
		}
}

void case_dirn_up() {
	int floor = elev_get_floor_sensor_signal(); 

	if (floor != -1){
		int smth_in_Q_over = 0; //variable; keeps track of if there is an order in any of the queues above or not 

		for (int j = floor; j < 4; j++){ //Check if it is some orders over the elevator 
			if (qm_get_order_in_Q_up(j) || qm_get_order_in_Q_down(j) || qm_get_order_in_Q_command(j)) {
				mm_set_motor_dir(DIRN_UP);
				smth_in_Q_over = 1;
				break;
			}
		}
		if (smth_in_Q_over == 0){ //there were no orders above 
			mm_set_motor_dir(DIRN_DOWN);
			mm_set_last_moving_motor_dir(DIRN_DOWN);
		}
	}
	else {}
}

void case_dirn_down(){
	int floor = elev_get_floor_sensor_signal(); 

	if (floor != -1){
		int smth_in_Q_under = 0; //variable; keeps track of if there is an order in any of the queues below or not 

		for (int i = floor ; i > -1; i--){//Check if it is some orders over the elevator 
			if (qm_get_order_in_Q_up(i) || qm_get_order_in_Q_down(i) || qm_get_order_in_Q_command(i)) {
				mm_set_motor_dir(DIRN_DOWN);
				smth_in_Q_under = 1;
				break;
			}
		}
		
		if (smth_in_Q_under == 0) { //there were no orders below
			mm_set_motor_dir(DIRN_UP);
			mm_set_last_moving_motor_dir(DIRN_UP);
		}
	}
	else{}
}


void sm_drive_direction_between_floors(){

	int last_driving_dir = mm_get_last_moving_motor_dir();

	switch(last_driving_dir) {

		case(DIRN_DOWN):
			case_dirn_down_between_floors();

			break;

		case(DIRN_UP):
			case_dirn_up_between_floors();
			break; 

		default:
			printf("Default; last moving dir \n");
		}
}

void case_dirn_up_between_floors() {
	int smth_in_Q_over = 0;	//variable; keeps track of if there are any orders in any of the queues above
		
	for (int j = previous_floor+1; j < 4; j++){ //Check if there are any orders above the elevator
		if (qm_get_order_in_Q_up(j) || qm_get_order_in_Q_down(j) || qm_get_order_in_Q_command(j)) {
			mm_set_motor_dir(DIRN_UP);
			smth_in_Q_over = 1;
			
			break;
		}
	}
	if (smth_in_Q_over == 0){ // There were no orders above
		mm_set_motor_dir(DIRN_DOWN);
		mm_set_last_moving_motor_dir(DIRN_DOWN);
		 
	}
	else {}
}

void case_dirn_down_between_floors(){
	int smth_in_Q_under = 0; //variable; keeps track of if there are any orders in any of the queues below

	for (int i = previous_floor-1; i > -1; i--){ //Check if there are any orders below the elevator
		if (qm_get_order_in_Q_up(i) || qm_get_order_in_Q_down(i) || qm_get_order_in_Q_command(i)) {
			mm_set_motor_dir(DIRN_DOWN);
			smth_in_Q_under = 1;

			break;
		}
	}
	if (smth_in_Q_under == 0) { // There were no orders below
		mm_set_motor_dir(DIRN_UP);
		mm_set_last_moving_motor_dir(DIRN_UP);
		
	}
	else{}
}
