#Compiler
CC := gcc

INC := inc
SRC := src
OUT := out

CFLAGS := -Wall -Werror -Wpedantic -Wextra -std=c99 -I $(INC)/ -lm

C_ALL := $(wildcard $(SRC)/*.c)

OBJ := $(C_ALL:$(SRC)/%.c=$(OUT)/%.o)

app.exe: $(OBJ)
	@$(CC) -o $@ $(OBJ)

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	@rm -f *.exe $(OUT)/*.o

