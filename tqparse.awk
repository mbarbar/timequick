#!/usr/bin/env awk -f

# TODO: will always output in seconds.

BEGIN {
    # Number of lines prefixed by 'tq_stop'.
    tq_entries = 0
}

/^tq_stop:/ {
    ++tq_entries
    if (NF < 3) {
        print "Bad input: '" $0 "' has less than 3 fields."
        exit 1
    }

    # Use NF as the time because the message cold have spaces.
    if (!match($NF, /[a-z]+/)) {
        print "Bad input: expected floating point followed by unit for time, not '" $NF "'."
        exit 1
    }

    time = substr($NF, 1, RSTART - 1)
    unit = substr($NF, RSTART, RLENGTH)

    # Message is $2 to $NF - 1
    msg = $2
    for (i = 3; i < NF; ++i) { msg = msg " " $i }

    msg = substr(msg, 1, length(msg) - 1)

    times[msg] += to_seconds(time, unit)
    ++freq[msg]
}

END {
    print "  ####### timequick #######"
    print "    # timequick entries: " NR - tq_entries
    for (msg in times) {
        print "    " "----- " msg " -----"
        printf "      " "Total time  : %.5f\n", times[msg]
        printf "      " "Frequency   : %d\n",   freq[msg]
        printf "      " "Average time: %.5f\n", times[msg] / freq[msg]
    }
}

function to_seconds(time, unit) {
    if (unit == "ns") {
        return time / 1000000000
    } else if (unit == "us") {
        return time / 1000000
    } else if (unit == "ms") {
        return time / 1000
    } else if (unit == "s") {
        return time
    } else {
        print "Bad time unit: '" unit "'"
        exit 2
    }
}
