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

default: 1.000373s
milliseconds: 1000.210931ms
microseconds: 1000192.322000us
nanoseconds: 1000096228.000000ns
seconds: 1.000321s
Inner: 1.000076s
Inner: 1.000406s
Inner: 1.000836s
Outer: 3.001339s

*/

