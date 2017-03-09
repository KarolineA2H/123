#include "Qmanager.h"

//Variables
static int queue_up[4] ={0}; 
static int queue_down[4] = {0};
static int queue_command[4]={0};  

void qm_set_order_in_Q_up (int floor, int bool_value){
	queue_up[floor] = bool_value;
}

void qm_set_order_in_Q_down(int floor, int bool_value){
	queue_down[floor] = bool_value;
}
void qm_set_order_in_Q_command(int floor, int bool_value){
	queue_command[floor] = bool_value;
}

int qm_get_order_in_Q_up( int floor){
	return queue_up[floor];
}

int qm_get_order_in_Q_down( int floor){
	return queue_down[floor];
}

int qm_get_order_in_Q_command(int floor){
	return queue_command[floor];
} 

void qm_delete_Q(){
	for(int x = 0; x < 4; x++) {
		queue_command[x] = 0;
		queue_up[x] = 0;
		queue_down[x] = 0;
	}
}

void qm_delete_executed_order(int floor){
	qm_set_order_in_Q_command(floor, 0);
	qm_set_order_in_Q_down(floor, 0);
	qm_set_order_in_Q_up(floor, 0);
}

int qm_is_Q_empty(){
	int x;
	for(int i =0; i<4; i++){
		x = qm_if_order_in_Q_at_current_floor(i); 
		if (x == 1) {return 0;}
	}
	return 1;
}

int qm_if_order_in_Q_at_current_floor(int floor){
	 if (qm_get_order_in_Q_up(floor) || qm_get_order_in_Q_down(floor) || qm_get_order_in_Q_command(floor)) {return 1;}
    else {return 0;}
}
