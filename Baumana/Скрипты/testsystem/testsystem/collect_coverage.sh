#!/bin/bash

./build_debug.sh
cd ./func_tests/scripts/ || return
./func_tests.sh
echo
cd ./../..
gcov ./main.c | head -n 2
./clean.sh
