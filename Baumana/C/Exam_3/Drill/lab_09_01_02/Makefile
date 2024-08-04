# Compiler name
CC:= gcc
# Variables
SRC:= src
INC:= inc
OUT:= out
# Flags for compile programm
CFLAGS:= -Wall -Werror -Wpedantic -std=c99 -I $(INC)/ -lm

# Common variables
C_ALL:=$(wildcard $(SRC)/*.c)

OBJ:=$(C_ALL:$(SRC)/%.c=$(OUT)/%.o)

app.exe: clean out $(OBJ)
	@$(CC) -o $@ $(OBJ)

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean out

clean: 
	@rm -f *.exe $(OUT)/*.o

out:
	@mkdir out
