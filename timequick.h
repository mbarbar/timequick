/* timequick.h
   Header only library to quickly time things.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef TIMEQUICK_H
#define TIMEQUICK_H

/* This allows nesting of start/stop calls, sort of like
   matching parentheses. A switch is available because
   working with a stack and dynamic allocation might add
   too much overhead for a lot of timing purposes.
   0 disables nesting.
 */
#define NEST 1

/* Time unit when printing. */
enum tq_unit {
        tq_SECONDS,
        tq_MILLISECONDS,
        tq_MICROSECONDS,
        tq_NANOSECONDS
};

/* Nodes of the nesting stack. */
struct tq_node {
        struct timespec start_time;
        struct tq_node *next;
};

/* Starting time when not nesting. */
static struct timespec tq_start_time = {0, 0};

#if NEST
/* Nesting stack. */
static struct tq_node *tq_stack = NULL;
#endif  /* #if NEST */

static enum tq_unit tq_output_unit = tq_SECONDS;

/* Set the time unit for printing. Only affects output, not resolution.
   Set to "seconds" by default.
 */
static void tq_set_unit(enum tq_unit unit) {
        tq_output_unit = unit;
}

/* Start timing. The next tq_stop will match the latest tq_start, like
   matching parentheses. msg is ignored, and only for user's readability.
 */
static void tq_start(char const *msg) {
#if NEST
        struct tq_node *new_node = (struct tq_node *)malloc(sizeof(struct tq_node));
        assert(new_node && "timequick: malloc failed.");

        clock_gettime(CLOCK_REALTIME, &(new_node->start_time));
        new_node->next = tq_stack;

        tq_stack = new_node;
#else
        clock_gettime(CLOCK_REALTIME, &tq_start_time);
#endif  /* #if NEST */
}

/* Stop timing, and print the time since the last tq_start with msg. */
static void tq_stop(char const *msg) {
        static struct timespec end_time;
        static double elapsed_time;
        static char const *unit = "s";

        /* If nesting, pop the stack, and put the start time into
           the global.
         */
#if NEST
        assert(tq_stack && "timequick: stack is empty.");
        memcpy(&tq_start_time, &(tq_stack->start_time),
               sizeof(struct timespec));

        struct tq_node *old_top = tq_stack;
        tq_stack = tq_stack->next;
        free(old_top);
#endif  /* if NEST */

        clock_gettime(CLOCK_REALTIME, &end_time);
        elapsed_time = (end_time.tv_nsec - tq_start_time.tv_nsec)
                       + (end_time.tv_sec - tq_start_time.tv_sec)
                         * 1000000000;

        switch (tq_output_unit) {
        case tq_SECONDS:
                unit = "s";
                elapsed_time /= 1000000000;
                break;
        case tq_MILLISECONDS:
                unit = "ms";
                elapsed_time /= 1000000;
                break;
        case tq_MICROSECONDS:
                unit = "us";
                elapsed_time /= 1000;
                break;
        case tq_NANOSECONDS:
                unit = "ns";
                break;
                /* elapsed_time is already sorted. */
        }

        printf("tq_stop: %s: %f%s\n", msg, elapsed_time, unit);
}

#endif  /* #ifndef TIMEQUICK_H */

