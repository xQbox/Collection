app.exe: lab_06_02.o construct.o io.o libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -o app.exe lab_06_02.o construct.o io.o

lab_06_02.o: lab_06_02.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c lab_06_02.c

construct.o: construct.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c construct.c 

io.o: io.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c io.c

clean: 
	rm -r *.o 	

delete:
	rm -r *.o *.exe
