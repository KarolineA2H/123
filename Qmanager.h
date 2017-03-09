
#ifndef QueueManager
#define QueueManager

#include <stdio.h>
#include "elev.h" //vil ikke ha denne her. er pga for å stoppe i en etg 

/*
Sets the element, indicated by 'floor', in the up-queue to 'bool_value'.
Bool_value equal to 1 means that there is an order at 'floor'.
The up-queue representes the BUTTON_CALL_UP buttons.
*/
void qm_set_order_in_Q_up (int floor, int bool_value);

/*
Sets the element, indicated by 'floor', in the down-queue to 'bool_value'.
Bool_value equal to 1 means that there is an order at 'floor'.
The up-queue representes the BUTTON_CALL_DOWN buttons.
*/
void qm_set_order_in_Q_down(int floor, int bool_value); 

/*
Sets the element, indicated by 'floor', in the command-queue to 'bool_value'.
Bool_value equal to 1 means that there is an order at 'floor'.
The up-queue representes the BUTTON_COMMAND buttons.
*/
void qm_set_order_in_Q_command(int floor, int bool_value); 

/*
This function handles the up-queue array.
Returns the value stored in the element, indicated by 'floor'.
*/
int qm_get_order_in_Q_up( int floor); 

/*
This function handles the down-queue array.
Returns the value stored in the element, indicated by 'floor'.
*/
int qm_get_order_in_Q_down( int floor); 

/*
This function handles thecommand-queue array.
Returns the value stored in the element, indicated by 'floor'.
*/
int qm_get_order_in_Q_command(int floor); 

/*
Deletes all the elevators orders. Sets all elements in all three queue arrays to 0.
*/
void qm_delete_Q(); 

/*
Deletes the order in all three queues. 
Sets the value stored in the element indicated by 'floor' to 0 
*/
void qm_delete_executed_order(int floor);

/*
Returns 0 if there are no orders in any of the queues.
*/
int qm_is_Q_empty(); 

/*
Returns 1 if there is an order at 'floor', 0 if not.
*/
int qm_if_order_in_Q_at_current_floor(int floor);


#endif
