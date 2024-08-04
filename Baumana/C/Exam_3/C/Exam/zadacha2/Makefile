СС 	:= gcc
INC	:= inc
OUT := out
SRC	:= src

ALL 	:= $(wildcard *.c)
OBJ		:= $(ALL:%.c=%.o)
FLAGS	:= -Wall -Werror -Wpedantic -std=gnu99 -Wextra

app.exe: $(OBJ)
	@$(CC) -o $@ $(OBJ)

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $< 

.PHONY: clean out

clean:
	@rm -f *.exe *.o

