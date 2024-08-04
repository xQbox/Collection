CC 	:= gcc

INC 	:= inc

OUT		:= out

SRC 	:= src

C_ALL 	:= $(wildcard $(SRC)/*.c)

OBJ 	:= $(C_ALL:$(SRC)/%.c=$(OUT)/%.o)

CFLAGS := -Wall -Werror -Wpedantic -Wextra -std=gnu99 -I $(INC)/

app.exe: $(OBJ)
	@$(CC) -o $@ $(OBJ)

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean out

clean:
	@rm -f *.exe $(OUT)/*.o
