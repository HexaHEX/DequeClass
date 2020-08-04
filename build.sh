#! /bin/bash

mkdir Build 2> /dev/null
cd Build
g++ ../main.cpp ../deque.cpp ../dequeexception.cpp ../deque_tests/*.cpp ../catch2/catch.hpp ../catch2/internal/*.cpp ../catch2/reporters/*.cpp ../catch2/external/clara.hpp -g -fprofile-arcs -ftest-coverage -O0 -std=c++11 -m64 -fPIC -pipe -lgcov -o ../deque.bin

exit 0

