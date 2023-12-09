#!/bin/bash 

NAME=$1

shift 1

mkdir -p build 
cd build
cmake ..
make ${NAME}App
