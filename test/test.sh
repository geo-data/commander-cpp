#!/bin/env bash

##
# Simple commander++ Test harness
#
# This loops through the commands specified in `./tests.txt`, executing them
# and testing them against the expected output in `expected/*.txt`.
#

count=1
failed=0

while read test; do
    echo "Test ${count}: ${test}"

    if test -f expected/${count}.txt; then
        $test 2>/dev/null | diff - expected/${count}.txt
    fi
    if test -f expected/${count}.err.txt; then
        $test 2>&1 >/dev/null | diff - expected/${count}.err.txt
    fi
    

    if test $? -eq 0; then
        echo "Test OK"
    else
        echo "Test FAILED"
        failed=`expr $failed + 1`
    fi

    count=`expr $count + 1`
done < tests.txt

if test $failed -gt 0; then
    echo "${failed} tests failed"
    exit $failed
fi
