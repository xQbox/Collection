CC 	:= gcc

INC := ./inc
OUT := ./out
SRC := ./src

CFLAGS := -Wall -Werror -std=c99 -Wpedantic -I $(INC)/

C_ALL := $(wildcard $(SRC)/*.c)

OBJ	:= $(C_ALL:$(SRC)/%.c=$(OUT)/%.o)

app.exe: clean $(OBJ)
	@$(CC) -o $@ $(OBJ)

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean out

out :
	@mkdir out
clean: 
	@rm -f *.exe $(OUT)/*.o

