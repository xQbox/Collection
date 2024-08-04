#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fno-omit-frame-pointer -g -fPIE -c *.c
clang -std=c99 -o -Wall -Werror -Wpedantic -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fno-omit-frame-pointer -g -fPIE -o app.exe *.o
