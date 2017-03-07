#include "elev.h"
#include "StateMachine.h"
#include "Initialize.h"
#include "Qmanager.h"
#include <stdio.h>


int main() {
    elev_initialize();
    while (1) {
        sm_check_stop_button();
        sm_check_button_pressed();

        sm_set_current_floor_and_indicator();

        sm_elev_move_or_stop();

        sm_order_in_Q_vs_current_floor(); 
    }
    return 0;
}
