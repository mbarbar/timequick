#!/usr/bin/python3

# Parses timequick output and prints some stats.
# TODO: currently expects all times in the file
# to be of the same unit.
# usage: ./tq_parse.sh filename

import re
import sys

TQ_STOP_PREFIX = "tq_stop: "
LABEL_TIME_SPLIT_RE = re.compile("(.*): (\d+(\.\d+)?)([a-z][a-z]?)")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: {} filename".format(sys.argv[0]))
        sys.exit(1)

    # "tq_stop label" --> (total time, frequency)
    labels = {}
    unit = ""

    infile = sys.argv[1]
    with open(infile, "r") as inf:
        for line in inf.readlines():
            if not line.startswith(TQ_STOP_PREFIX):
                continue

            # Clean up the line.
            line = line[len(TQ_STOP_PREFIX):]
            line = line.strip()

            groups = re.search(LABEL_TIME_SPLIT_RE, line)
            if groups:
                label = groups.group(1)
                time  = groups.group(2)
                # 4 because we use two groups for the time.
                unit  = groups.group(4)

                try:
                    totals = labels[label]
                    labels[label] = (totals[0] + float(time), totals[1] + 1)
                except:
                    labels[label] = (float(time), 1)

            else:
                # TODO: Maybe output as an option?
                # print("Bad format? '{}'".format(line))
                pass

    print("\n===== timequick: '{}' =====".format(infile))
    for label in labels:
        totals = labels[label]
        print("")
        print(" {}: ".format(label))
        print("   Total time taken  : {}".format(totals[0]))
        print("   Frequency         : {}".format(totals[1]))
        print("   Average time taken: {}".format(float(totals[0]) / totals[1]))
    print("\n===== timequick stats done =====\n".format(infile))


