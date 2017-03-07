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

        sm_elev_move_or_stop();

        sm_order_in_Q_vs_current_floor(); 

/*
        printf("\n\n");
        for (int i = 0; i < 4; i++){
            printf("Order for floor %d: %d\n", i+1, qm_get_order_in_Q_down(i));
        }

        printf("\n\n");

        for (int i = 0; i < 4; i++){
            printf("Order for floor %d: %d\n", i+1, qm_get_order_in_Q_up(i));
        }

        printf("\n\n");
        printf("\n\n");
        */
    }
    return 0;
}
