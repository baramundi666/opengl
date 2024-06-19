#!/bin/bash

mkdir -pv build
cd build || exit
cmake .. -B .
make
./opengl
rm opengl