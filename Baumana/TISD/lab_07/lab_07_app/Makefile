# constants
CC 	:= gcc
INC	:= inc
OUT	:= out
SRC	:= src

CFLAGS	:= -Wall -Werror -Wpedantic -std=c99 -Wextra -I $(INC)/

C_ALL 	:= $(wildcard $(SRC)/*.c)

OBJ	:= $(C_ALL:$(SRC)/%.c=$(OUT)/%.o)

app.exe: $(OBJ)
	@$(CC) -o $@ $(OBJ)

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean 

clean:
	@rm -f *.exe $(OUT)/*.o

