/* timequick.h
   Header only library to quickly time things.
 */

#ifndef TIMEQUICK_H
#define TIMEQUICK_H

/* Time resolution when printing. */
enum tq_resolution {
        tq_SECONDS,
        tq_MILLISECONDS,
        tq_MICROSECONDS,
        tq_NANOSECONDS
};

/* Set the time resolution for printing. Only affects output. */
static void tq_set_resolution(enum tq_resolution resolution) {

}

/* Start timing. */
static void tq_start(char *msg) {

}

/* Stop timing, and print the time since the last tq_start. */
static void tq_stop(char *msg) {

}

#endif
