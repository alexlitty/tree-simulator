#!/bin/bash
if [ $# -eq 0 ]
  then
    make linux64
else
    make linux64 -B -j 2
fi
if [ "$?" -eq "0" ]; then
  cd ./bin/linux64
  ./treesimulator
fi
