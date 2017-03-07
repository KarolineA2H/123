#include "Timer.h"

double t_get_wall_time(){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void t_start_timer(){
	time_Stamp = t_get_wall_time();
}

int t_check_time(){
	
	if (t_get_wall_time()- time_Stamp >= 3){
		return 1;
	}
	else {
		return 0;
	}
}