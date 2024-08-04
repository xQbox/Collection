#!/bin/bash

gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -O3 -g --coverage *.c
gcc --coverage *.o -o app.exe -lm
