CC 	:= gcc

C_FLAGS 	:= -Wall -Werror -Wpedantic -Wextra -std=gnu99

C_ALL 		:= $(wildcard *.c)

OBJ			:= $(C_ALL:%.c=%.o)


app.exe: $(OBJ)
	$(CC) -o $@ $<

%.o: %.c
	$(CC) $(C_FLAGS) -o $@ -c $<

.PHONY: clean

clean:
	@rm -f *.exe *.o