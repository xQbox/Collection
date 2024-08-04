CC		:= gcc

C_ALL 	:= $(wildcard *.c)

FLAGS	:= -Wall -Werror -Wpedantic -std=gnu99 -Wextra

OBJ		:= $(C_ALL:%.c=%.o)

app.exe: $(OBJ)
	@$(CC) -o $@ $^

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $<

.PHONY: clean
 
clean:
	@rm -f *.exe *.o

