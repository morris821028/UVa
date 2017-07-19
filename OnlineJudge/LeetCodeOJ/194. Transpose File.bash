#!/bin/bash
# Read from the file file.txt and print its transposed content to stdout.

awk '
{
    for (i = 1; i <= NF; i++) {
        if (NR == 1) {
            a[i] = $i;
        } else {
            a[i] = a[i] " " $i;
        }
    }
}
END {
    for (i = 1; a[i] != ""; i++) {
        print a[i];
    }
}' file.txt
