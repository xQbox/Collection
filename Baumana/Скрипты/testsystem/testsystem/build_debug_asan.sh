#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -fsanitize=address -fno-omit-frame-pointer -g -c *.c
clang -std=c99 -o -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -fsanitize=address -fno-omit-frame-pointer -g -o app.exe *.o
