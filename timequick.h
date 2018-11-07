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

/* Set the time resolution for printing. Only affects output. */
static void tq_set_resolution(enum tq_resolution resolution) {

}

/* Start timing. */
static void tq_start(char *msg) {
        clock_gettime(CLOCK_REALTIME, &tq_start_time);
}

/* Stop timing, and print the time since the last tq_start. */
static void tq_stop(char *msg) {
        static struct timespec tq_end_time;
        static long elapsed_s, elapsed_ns;

        clock_gettime(CLOCK_REALTIME, &tq_end_time);
        elapsed_s = tq_end_time.tv_sec - tq_start_time.tv_sec;
        elapsed_ns = tq_end_time.tv_nsec - tq_start_time.tv_nsec;

        printf("%s: %lds %ldns\n", msg, elapsed_s, elapsed_ns);
}

#endif
