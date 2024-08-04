CC 	:= gcc

CFLAGS := -Wall -Werror -std=gnu99 -g

INC 	:= ./inc
OUT 	:= ./out
SRC		:= ./src

ALL_C	:= $(wildcard $(SRC)/*.c)


OBJ 	:= $(ALL_C:$(SRC)/%.c=$(OUT)/%.o)

app.exe: main.o libba.a 
	@$(CC) -o $@ $^

libba.a: book.o book_array.o
	@ar -cr $@ $^ 

book.o: book.c book.h error.h
	@$(CC) $(CFLAGS) -c $<

book_array.o: book_array.c book_array.h error.h
	@$(CC) $(CFLAGS) -c $<


main.o:  main.c book_array.h book.h error.h
	@$(CC) $(CFLAGS) -c $^

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $@ 

.PHONY: clean

clean:
	@rm -f *.exe *.o