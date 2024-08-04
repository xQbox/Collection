#!/bin/bash
# -Werror -Wpedantic -Wextra -Wfatal-errors
if [ -n "$1" ]; then
    cd ./../src/ && 
    gcc -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wfatal-errors -Werror -Wvla -std=c99 -c *.c &&
    mv *.o ./../obj &&
    cd ./../obj/ &&
    gcc -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wfatal-errors -Werror -Wvla -std=c99 *.o -o ./../build/$1 -lm &&
    rm -f * &&
    echo "Compilation succesfull"
else 
    echo "Write name of exe file"
fi
