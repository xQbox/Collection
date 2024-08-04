# constants
CC 	:= gcc


CFLAGS	:= -Wall -Werror  -std=gnu99 -Wextra 

C_ALL 	:= $(wildcard *.c)

OBJ	:= $(C_ALL:%.c=%.o)

app.exe: $(OBJ)
	@$(CC) -o $@ $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean 

clean:
	@rm -f *.exe *.o

