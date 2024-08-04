app: lab_04_02.o libmy.o
	gcc -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wfatal-errors -Werror -Wvla -std=c99 -o app lab_04_02.o libmy.o -lm

lab_04_02.o: lab_04_02.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wfatal-errors -Werror -Wvla -std=c99 -c lab_04_02.c
    
libmy.o: libmy.h libmy.c
	gcc -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wfatal-errors -Werror -Wvla -std=c99 -c libmy.c

test_libmy.o: libmy.h test_libmy.c
	gcc -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wfatal-errors -Werror -Wvla -std=c99 -c test_libmy.c

test: test_libmy.o libmy.o
	gcc -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wfatal-errors -Werror -Wvla -std=c99 -o test test_libmy.o libmy.o -lm

clean: 
	rm -r *.o