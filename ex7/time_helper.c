#include <sys/time.h>
#include <time.h>
#include <stdio.h>

static double gtod_ref_time_sec = 0.0;

double last_time = 0.0;

/* Adapted from the bl2_clock() routine in the BLIS library */

double dclock()
{
  double         the_time, norm_sec;
  struct timeval tv;
  gettimeofday( &tv, NULL );
  if ( gtod_ref_time_sec == 0.0 )
    gtod_ref_time_sec = ( double ) tv.tv_sec;
  norm_sec = ( double ) tv.tv_sec - gtod_ref_time_sec;
  the_time = norm_sec + tv.tv_usec * 1.0e-6;
  return the_time;
}

void start_clock() {
    last_time = dclock();
}

void stop_clock() {
    printf("Time: %lf\n", dclock() - last_time);
}

