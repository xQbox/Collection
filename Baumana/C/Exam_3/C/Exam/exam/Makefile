CC 	:= gcc
#
ALL	:= $(wildcard *.c)
OBJ	:= $(ALL:%.c=%.o)

FLAGS	:= -Wall -Werror -Wpedantic -Wextra -std=gnu99

app.exe: $(OBJ)
	$(CC) -o $@ $^

%.o: %c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -f *.exe *.o