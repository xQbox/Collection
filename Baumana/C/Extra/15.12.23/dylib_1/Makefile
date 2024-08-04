CC 	:= gcc
C_FLAGS 	:= -std=gnu99 -Wall -Werror -g


app.exe : main.o libba.so
	@$(CC) -o $@ $^

libba.so: book.o book_array.o 
	@$(CC) -o $@ -shared $^

# -l -L для компоновки библиотекее в разных папках
# -L путь к каталогу где нужно искать библиотеку
# -l имя библиотеки(только существенное имя библиотеки) (ba) для именования libXYZ.a

book.o: book.c book.h error.h
	@$(CC) $(C_FLAGS) -fpic  -c $^

#-fPIC как вариант

book_array.o: book_array.c book_array.h error.h
	@$(CC) $(C_FLAGS) -fpic -c $^

main.o: main.c book_array.h book.h error.h
	@$(CC) $(C_FLAGS) -c $^

.PHONY: clean

clean:
	rm -f *.exe *.o
