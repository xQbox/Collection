CC 			:= gcc


INC 		:= inc
OUT			:= out
SRC			:= src

C_ALL		:= $(wildcard $(SRC)/*.c)

# FLAGS 		:= -Wall -Werror -Wpedantic -std=gnu99 -Wextra -I $(INC)/
# FLAGS 			:= -Wall -std=gnu99 -I $(INC)/
FLAGS 		:= -Wall -std=c99 
OBJ			:= $(C_ALL:$(SRC)/%.c=$(OUT)/%.o)

app.exe: $(OBJ)
	@$(CC) -o $@ $^ -lm

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(FLAGS) -o $@ -c $<

.PHONY: clean

clean: 
	@rm -f *.exe $(OUT)/*.o

