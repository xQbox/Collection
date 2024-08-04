CC	:= gcc
_ALL	:= $(wildcard *.c)
OBJ		:= $(_ALL:%.c=%.o)
FLAGS	:= -Wall -Werror -Wpedantic -Wextra -std=gnu99

app.exe: $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f *.exe *.o