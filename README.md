# timequick

timequick is a header-only library to quickly (but coarsely)
time C/C++ code.
Timing is done to nanosecond resolution, but overhead coming from timequick is unaccounted for.

## Usage

Simply `#include` the `timequick.h` file, no linking needed.

Call `tq_start` to start timing, and `tq_stop` to record the time from the last `tq_start` call.
A message string could be added, and is used in the output of `tq_stop`.
The `msg` parameter of `tq_start` has no functionality, but can be used for readability.
Nesting is possible, and works like matching or balancing parentheses.
`tq_set_unit` can be used to set the unit in the output (this does not affect the timing resolution).

An example of usage is available in `example.c`.

## Requirements

timequick only uses function from the C standard and POSIX.

## Configuration

### Nesting

Nesting is possible, like matching or balancing parentheses.
This uses a dynamically allocated stack, so might make timing even coarser.
To disable the stack, change `#define NEST 1` to `#define NEST 0` in `timequick.h`.

### Output unit

`tq_set_unit` can be called with any value from the following `enum` to set the unit used for the output.

`
enum tq_unit {
        tq_SECONDS,
        tq_MILLISECONDS,
        tq_MICROSECONDS,
        tq_NANOSECONDS
};
`
