#compiler 
CC		:= gcc



INC 	:= inc
OUT		:= out
SRC		:= src

CLFAGS 	:= -Wall -Werror -Wextra -Wpedantic -std=c99 -I $(INC)/

C_ALL 	:= $(wildcard $(SRC)/*.c)

OBJ		:= $(C_ALL:$(SRC)/%.c=$(OUT)/%.o)

app.exe: $(OBJ)
	@$(CC) -o $@ $(OBJ) -lm

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CLFAGS) -o $@ -c $<




.PHONY: clean

clean:
	@rm -f *.exe $(OUT)/*.o
