#!/bin/bash

mkdir build
cd build || exit
cmake .. -B .
make
./opengl