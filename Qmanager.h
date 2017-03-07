
#ifndef QueueManager
#define QueueManager

#include <stdio.h>
#include "elev.h" //vil ikke ha denne her. er pga for å stoppe i en etg 



// bool_value is the value in the array, representing if the 
// elevator has an order there or not
void qm_set_order_in_Q_up (int floor, int bool_value);
void qm_set_order_in_Q_down(int floor, int bool_value); 
void qm_set_order_in_Q_command(int floor, int bool_value); 

int qm_get_order_in_Q_up( int floor); 
int qm_get_order_in_Q_down( int floor); 
int qm_get_order_in_Q_command(int floor); 

//sletter alle bestillingene i køen 
void qm_delete_Q(); 

//sletter bestillingen fra køen
void qm_delete_executed_order(int floor);

//returnerer 1 om vi ikke har noe bestillinger i køen
int qm_is_Q_empty(); 

//det er en bestilling i køen 
int qm_if_order_in_Q_at_current_floor(int floor);


#endif