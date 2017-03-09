#ifndef TimerHFile
#define TimerHFile

#include <stdio.h>
#include <sys/time.h>

/*
Function given for an earlier Linux and C-lab
Returns the number of seconds passed since 1. January 1970.
*/
double t_get_wall_time();

/*
Set the static variable time_stamp to value returned by get_wall_time()
*/
void t_start_timer();

/*
Checks if 3 seconds have passed and returns 1 if it has, retunrs 0 if not.
*/
int t_check_timer();

#endif
