CC 	:= gcc
C_FLAGS	:= -std=c99 -Wall -Werror -g 
#NO -Wpedantic

app.exe: main.o
	@$(CC) -o $@ main.o -ldl
# -ldl указываем ключ для подключения динамической библиотеки

main.o: main.c book.h book_array.h error.h
	@$(CC) $(C_FLAGS) -c $<

.PHONY: clean

clean:
	@rm -f *.o *.exe