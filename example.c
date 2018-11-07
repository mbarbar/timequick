/* example.c
   A file showing timequick usage, and to
   run some quick tests.
 */

#include <stdlib.h>

#include "timequick.h"

int main(void) {
        tq_set_resolution(tq_SECONDS);
        tq_start(NULL);
        tq_stop("not null");
}

