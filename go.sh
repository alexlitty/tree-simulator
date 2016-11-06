#!/bin/bash
make linux64
if [ "$?" -eq "0" ]; then
  cd ./bin/linux64
  ./treesimulator
fi
