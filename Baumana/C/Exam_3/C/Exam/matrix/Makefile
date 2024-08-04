CC := gcc

C_ALL := $(wildcard *.c)

OBJ		:= $(C_ALL:%.c=%.o)

FLAGS	:= -Wall -Werror -Wpedantic -Wextra -std=gnu99

app.exe: $(OBJ)
	@$(CC) -o $@ $(OBJ)

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $<

.PHONY: clean

cleam:
	@rm -f *.exe *.o