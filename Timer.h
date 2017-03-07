#ifndef TimerHFile
#define TimerHFile


#include <stdio.h>
#include <sys/time.h>

static double time_Stamp;

// utlevert funksjon som henter ant sekunder siden 1.jan 1970
double t_get_wall_time();

//starter timeren, setter initial_time lik get_wall_time()
void t_start_timer();

//Returnerer 1 hvis det har gått 3 sekunder, og 0 ellers
int t_check_time();
#endif