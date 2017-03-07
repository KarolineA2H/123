#include <stdio.h>

#include "Initialize.h"
#include "MotorManager.h"
#include "elev.h"


void elev_initialize() {
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
    }

	if (elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_DOWN);
		mm_set_last_moving_motor_dir(DIRN_DOWN);

		printf("motor sensor signal = -1\n");
		while (elev_get_floor_sensor_signal() == -1) {}
	}

	elev_set_motor_direction(DIRN_STOP);
	mm_set_motor_dir(DIRN_STOP);
	mm_set_last_moving_motor_dir(DIRN_DOWN);
	printf("setter last_motor direction til NED\n");

    elev_set_floor_indicator(elev_get_floor_sensor_signal());
}