#!/bin/bash

make clean
make 

(time ./Mcq ) 2> tempo.txt &
gprof ./Mcq > Profile.txt
