#!/bin/sh 
FILES=grammars/*
for f in $FILES
do
    echo "Running $f..."
    ./rsg "$f" > myOutput.txt
    ./rsg_ref "$f" > refOutput.txt
    if diff -q myOutput.txt refOutput.txt; then
        echo "Passed."
    else
        echo "FAILED!."
        diff myOutput.txt refOutput.txt
    fi
    rm myOutput.txt
    rm refOutput.txt
done
