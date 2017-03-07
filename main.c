#include "elev.h"
#include "StateMachine.h"
#include "Initialize.h"

#include <stdio.h>


int main() {
    elev_initialize();
    sm_timer_handler(); 

    while (1) {
        sm_set_current_floor_and_indicator();

        //ha en funksjon som sjekker om vi skal stoppe i en etasje
        //må legge inn noe for at den ikke skal stoppe i en etasje som skal motsatt vei



        //kan puttes i en funksojn med en else, der elsen kjører dersom det er noe i køen.
        //det inni elsen bestemmer hvilken vei heisen skal begynne å kjøre etter å ha stoppet.
        if(sm_elev_on_standby()){
            //har satt motor dir til STOP i sm_elev_on_standby
        }
        else { //vet at køen ikke er tom
            //masse dritt
        }

        //kan puttes inni en egen funksjon for knappetrykk.
        sm_check_stop_button();
        sm_check_button_pressed();

        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }
    }
    return 0;
}
