app.exe: lab_05_04.o libmy.o
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -o app.exe libmy.o lab_05_04.o

lab_05_04.o: lab_05_04.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c lab_05_04.c

libmy.o: libmy.c libmy.h
	gcc -Wall -Wextra -Wpedantic -Wfatal-errors -Werror -Wvla -std=c99 -c libmy.c
    
clean:
	rm -r *.o *.exe 
    