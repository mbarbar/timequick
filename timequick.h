/* timequick.h
   Header only library to quickly time things.
 */

#include <assert.h>
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

/* Time resolution when printing. */
enum tq_resolution {
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

static struct timespec tq_start_time = {0, 0};
/* Nesting stack. */
static struct tq_node *tq_stack = NULL;
static enum tq_resolution tq_output_resolution = tq_SECONDS;

/* Set the time resolution for printing. Only affects output.
   Set to "seconds" by default.
 */
static void tq_set_resolution(enum tq_resolution resolution) {
        tq_output_resolution = resolution;
}

/* Start timing. */
static void tq_start(char *msg) {
#if NEST
        struct tq_node *new_node = malloc(sizeof(struct tq_node));
        assert(new_node && "timequick: malloc failed.");

        clock_gettime(CLOCK_REALTIME, &(new_node->start_time));
        new_node->next = tq_stack;

        tq_stack = new_node;
#else
        clock_gettime(CLOCK_REALTIME, &tq_start_time);
#endif
}

/* Stop timing, and print the time since the last tq_start. */
static void tq_stop(char *msg) {
        static struct timespec end_time;
        static double elapsed_time;
        static char *units = "s";

        /* If nesting, pop the stack, and put the start time into
           the global.
         */
#ifdef NEST
        assert(tq_stack && "timequick: stack is empty.");
        memcpy(&tq_start_time, &(tq_stack->start_time),
               sizeof(struct timespec));

        struct tq_node *old_top = tq_stack;
        tq_stack = tq_stack->next;
        free(old_top);
#endif

        clock_gettime(CLOCK_REALTIME, &end_time);
        elapsed_time = (end_time.tv_nsec - tq_start_time.tv_nsec)
                       + (end_time.tv_sec - tq_start_time.tv_sec)
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
