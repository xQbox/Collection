CC 		:= gcc

INC 		:= inc

CFLAGS 		:= -Wall -Werror -std=c99 -Wpedantic -Wextra -I inc/ -lm

OUT		:= out
SRC		:= src

C_ALL 		:= $(wildcard $(SRC)/*.c)

OBJ 		:= $(C_ALL:$(SRC)/%.c=$(OUT)/%.o)


app.exe: $(OBJ)
	@$(CC) -o $@ $(OBJ)

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	@rm -f $(OUT)/*.o *.exe

