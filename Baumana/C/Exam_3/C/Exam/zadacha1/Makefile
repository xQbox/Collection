CC 	:= gcc
INC	:= inc
OUT := out
SRC	:= src

C_ALL 	:= $(wildcard *.c)

OBJ		:= $(C_ALL:%.c=%.o)

C_FLAGS	:= -Wall -Werror -Wpedantic -Wextra -std=gnu99 

app.exe: $(OBJ)
	@$(CC) -o $@ $(OBJ) -lm

%.o: %.c
	@$(CC) $(C_FLAGS) -o $@ -c $<

.PHONY: clean out

clean: 
	@rm -f *.exe *.o