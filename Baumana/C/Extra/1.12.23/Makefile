CC 			:= gcc
INC 		:= inc

CFLAGS 		:= -Wall -Werror -Wpedantic -std=c99

ALL_C		:= $(wildcard *.c)

OBJ			:= $(ALL_C:%.c=%.o)

app.exe:	 $(OBJ)
	$(CC) -o $@ $(OBJ) 

%.o:  %.c
	$(CC) $(CFLAGS) -o $@ -c $<