/* example.c
   A file showing timequick usage, and to
   run some quick tests.
 */

#include "timequick.h"

#include <stdlib.h>
#include <unistd.h>

int main(void) {
        tq_start(NULL);
        sleep(1);
        tq_stop("default");

        tq_set_unit(tq_MILLISECONDS);
        tq_start(NULL);
        sleep(1);
        tq_stop("milliseconds");

        tq_set_unit(tq_MICROSECONDS);
        tq_start(NULL);
        sleep(1);
        tq_stop("microseconds");

        tq_set_unit(tq_NANOSECONDS);
        tq_start(NULL);
        sleep(1);
        tq_stop("nanoseconds");

        tq_set_unit(tq_SECONDS);
        tq_start(NULL);
        sleep(1);
        tq_stop("seconds");

        /* For nesting. */
        tq_start("Outer");
        for (int i = 0; i < 3; ++i) {
                tq_start("Inner");
                sleep(1);
                tq_stop("Inner");
        }
        tq_stop("Outer");
}

/*
Example output:

tq_stop: default: 1.000173s
tq_stop: milliseconds: 1000.119064ms
tq_stop: microseconds: 1000115.943000us
tq_stop: nanoseconds: 1000069660.000000ns
tq_stop: seconds: 1.000099s
tq_stop: Inner: 1.000074s
tq_stop: Inner: 1.000073s
tq_stop: Inner: 1.000103s
tq_stop: Outer: 3.000333s

*/

