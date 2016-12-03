#!/bin/bash

for i in $( seq 0 9 )
do
    ./bin/map_gen maps/$i
done
