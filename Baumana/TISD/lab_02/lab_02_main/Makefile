# Compiler 
CC := gcc

# Directories
OUT := ./out
INC := ./inc
SRC := ./src

# gcc keys
CFLAGS := -Wall -Werror -Wfatal-errors -Wpedantic -Wextra -std=c99 -I $(INC) -lm 
LM_FLAG := -lm


# Included depends 
SRCS := $(wildcard $(SRC)/*.c)

# Object's files
OBJECTS := $(SRCS:$(SRC)/%.c=$(OUT)/%.o)


app.exe: $(OBJECTS)
	@$(CC) -o $@ $(OBJECTS) -lm

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<



.PHONY: clean 

clean:
	@rm *.exe $(OUT)/*.o

.DEFAULT_GOAL: app.exe
