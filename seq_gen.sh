#!/bin/bash

for i in $( seq 0 9 )
do
    for j in $( seq 0 9 )
    do
        ./bin/seq_gen maps/$i routes/$i$j
    done
done
