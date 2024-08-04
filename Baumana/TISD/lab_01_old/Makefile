app.exe: lab_01.o basic.o io.o libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -o app.exe lab_01.o basic.o io.o

lab_01.o: lab_01.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c lab_01.c

basic.o: basic.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c basic.c 

io.o: io.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c io.c

clean: 
	rm -r *.o 	

delete:
	rm -r *.o *.exe
