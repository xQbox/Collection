#!/bin/bash
if [ -n "$1" ]; then
	cd ./../src &&
	gcc -Wall -Wextra -Wpedantic -Werror -Wfloat-equal -Wfloat-conversion -Wvla -std=c99 -c *.c &&
	mv *.o ./../obj &&
	cd ./../obj &&
	gcc -Wall -Wextra -Wpedantic -Werror -Wfloat-equal -Wfloat-conversion -Wvla -std=c99 -o ./../build/$1 *.o -lm &&
	rm -f *.o &&
	echo "Compile successful"
else
	echo "Write parametr"
fi
