/* example.c
   A file showing timequick usage, and to
   run some quick tests.
 */

#include <stdlib.h>
#include <unistd.h>

#include "timequick.h"

int main(void) {
        tq_start(NULL);
        sleep(1);
        tq_stop("default");

        tq_set_resolution(tq_MILLISECONDS);
        tq_start(NULL);
        sleep(1);
        tq_stop("milliseconds");

        tq_set_resolution(tq_MICROSECONDS);
        tq_start(NULL);
        sleep(1);
        tq_stop("microseconds");

        tq_set_resolution(tq_NANOSECONDS);
        tq_start(NULL);
        sleep(1);
        tq_stop("nanoseconds");

        tq_set_resolution(tq_SECONDS);
        tq_start(NULL);
        sleep(1);
        tq_stop("seconds");
}

