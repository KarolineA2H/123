
#include "QueueManager.h" 

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


//returnerer 1 om det er match mellom etg og at det finnes en bestilling på denne etg
int qm_check_current_order_floor_and_ord(int floor){
	if(qm_get_order_in_Q_up(floor)|| qm_get_order_in_Q_down(floor) || qm_get_order_in_Q_command(floor)){
		return 1; // det er match mellom gjeldende etg og betilinng i en av bestillings arrayene
	}
	else {return 0}; //vi trenger ikke å stoppe. 
}

//sletter alle bestillingene i køen 
void qm_delete_Q(){
	for(int x = 0; x < 4; x++) {
		queue_command[x] = 0;
		queue_up[x] = 0;
		queue_down[x] = 0;
	}

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

//sletter bestillingen fra køen
void qm_delete_executed_order(int floor){
	qm_set_order_in_Q_command(floor, 0);
	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);//Skal state machinenen sette lys så er dette feil. 

	qm_set_order_in_Q_down(floor, 0);
	//elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);

	qm_set_order_in_Q_up(floor, 0);
	//elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
}

//returnerer 1 om vi ikke har noe bestillinger i køen
//smør på flesk??
int qm_if_q_is_empty(); 
//det er en bestilling i køen 
//returnerer 1 om vi har noe i bestillingen 
int qm_if_order_in_Q(int floor){
	 if (qm_get_order_in_Q_up(floor) || qm_get_order_in_Q_command(floor) || qm_get_order_in_Q_down(floor)) {return 1;}
    else {return 0;}
}
