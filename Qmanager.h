
#ifndef QueueManager
#define QueueManager

#include <stdio.h>
#include "elev.h" //vil ikke ha denne her. er pga for å stoppe i en etg 

//Variabler 

//Køen er håndtert med tre arrany
//array for bestillingsknappene opp, ned og etg knappene 

static int queue_up[4] ={0}; //plass for 4 etg finnes ikke som knapp 
static int queue_down[4] ={0} //plass for 1. etg finnes ikke som kan
static int queue_sommand[4]={0} 

// bool_value is the value in the array, representing if the 
// elevator has an order there or not
void qm_set_order_in_Q_up (int floor, int bool_value);
void qm_set_order_in_Q_down(int floor, int bool_value); 
void qm_set_order_in_Q_command(int floor, int bool_value); 

int qm_get_order_in_Q_up( int floor); 
int qm_get_order_in_Q_down( int floor); 
int qm_get_order_in_Q_command(int floor); 


//returnerer 1 om det er match mellom etg og at det finnes en bestilling på denne etg
int qm_check_current_order_floor_and_ord(int floor);

//sletter alle bestillingene i køen 
void qm_delete_Q(); 

//sletter bestillingen fra køen
void qm_delete_executed_order(int floor);

//returnerer 1 om vi ikke har noe bestillinger i køen
int qm_if_q_is_empty(); 
//det er en bestilling i køen 
int qm_if_order_in_Q(int floor);

#endif 