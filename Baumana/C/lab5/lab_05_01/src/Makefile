app.exe: lab_05_01.o libmy.o
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -o app.exe lab_05_01.o libmy.o 

lab_05_01.o: lab_05_01.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c lab_05_01.c

libmy.o: libmy.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c libmy.c

clean: 
	rm -r *.o *.exe