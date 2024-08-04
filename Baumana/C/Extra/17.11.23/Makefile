CC := gcc
INC := inc
CFLAGS := -Wall -Werror -Wpedantic -std=c99 -I $(INC)/ -lm

C_ALL := $(wildcard *.c)


OBJ := $(C_ALL:%.c=%.o)

app.exe: $(OBJ)
	$(CC) -o $@ $(OBJ) 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
