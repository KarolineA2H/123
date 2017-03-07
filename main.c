#include "elev.h"
#include "StateMachine.h"
#include "Initialize.h"
#include "Qmanager.h"
#include <stdio.h>


int main() {
    elev_initialize();
    sm_timer_handler(); 

    while (1) {
        sm_check_stop_button();
        sm_check_button_pressed();

        sm_set_current_floor_and_indicator();

        //ha en funksjon som sjekker om vi skal stoppe i en etasje
        //må legge inn noe for at den ikke skal stoppe i en etasje som skal motsatt vei


        sm_elev_move_or_stop();
        sm_order_in_Q_vs_current_floor(); 
        //kan puttes inni en egen funksjon for knappetrykk.

        // Change direction when we reach top/bottom floor
        /*if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }*/
        printf("\n\n");
        for (int i = 0; i < 4; i++){
            printf("Order for floor %d: %d\n", i+1, qm_get_order_in_Q_down(i));
        }

        printf("\n\n");
    }
    return 0;
}
