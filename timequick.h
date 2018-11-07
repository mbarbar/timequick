/* timequick.h
   Header only library to quickly time things.
 */

#include <time.h>
#include <stdio.h>

#ifndef TIMEQUICK_H
#define TIMEQUICK_H

/* Time resolution when printing. */
enum tq_resolution {
        tq_SECONDS,
        tq_MILLISECONDS,
        tq_MICROSECONDS,
        tq_NANOSECONDS
};

static struct timespec tq_start_time;
static enum tq_resolution tq_output_resolution = tq_SECONDS;

/* Set the time resolution for printing. Only affects output.
   Set to "seconds" by default.
 */
static void tq_set_resolution(enum tq_resolution resolution) {
        tq_output_resolution = resolution;
}

/* Start timing. */
static void tq_start(char *msg) {
        clock_gettime(CLOCK_REALTIME, &tq_start_time);
}

/* Stop timing, and print the time since the last tq_start. */
static void tq_stop(char *msg) {
        static struct timespec tq_end_time;
        static double elapsed_time;
        static char *units = "s";

        clock_gettime(CLOCK_REALTIME, &tq_end_time);
        elapsed_time = (tq_end_time.tv_nsec - tq_start_time.tv_nsec)
                       + (tq_end_time.tv_sec - tq_start_time.tv_sec)
                         * 1000000000;

        switch (tq_output_resolution) {
        case tq_SECONDS:
                units = "s";
                elapsed_time /= 1000000000;
                break;
        case tq_MILLISECONDS:
                units = "ms";
                elapsed_time /= 1000000;
                break;
        case tq_MICROSECONDS:
                units = "us";
                elapsed_time /= 1000;
                break;
        case tq_NANOSECONDS:
                units = "ns";
                break;
                /* elapsed_time is already sorted. */
        }

        printf("%s: %f%s\n", msg, elapsed_time, units);
}

#endif
