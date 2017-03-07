
#include "Qmanager.h"

//Variabler 

//Køen er håndtert med tre arrany
//array for bestillingsknappene opp, ned og etg knappene 

static int queue_up[4] ={0}; //plass for 4 etg finnes ikke som knapp 
static int queue_down[4] = {0}; //plass for 1. etg finnes ikke som kan
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

//sletter alle bestillingene i køen 
void qm_delete_Q(){
	for(int x = 0; x < 4; x++) {
		queue_command[x] = 0;
		queue_up[x] = 0;
		queue_down[x] = 0;
	}
}

//sletter bestillingen fra køen
void qm_delete_executed_order(int floor){
	qm_set_order_in_Q_command(floor, 0);

	qm_set_order_in_Q_down(floor, 0);
	
	qm_set_order_in_Q_up(floor, 0);
}

//returnerer 1 om vi ikke har noe bestillinger i køen
//smør på flesk??
int qm_is_Q_empty(){
	int x;
	for(int i =0; i<4; i++){
		x = qm_if_order_in_Q_at_current_floor(i); 
		if (x == 1) {return 0;}
	}
	return 1;
}

//det er en bestilling i køen 
//returnerer 1 om vi har noe i bestillingen
int qm_if_order_in_Q_at_current_floor(int floor){
	 if (qm_get_order_in_Q_up(floor) || qm_get_order_in_Q_down(floor) || qm_get_order_in_Q_command(floor)) {return 1;}
    else {return 0;}
}
