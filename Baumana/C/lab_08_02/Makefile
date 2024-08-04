INC := ./inc
OUT := ./out
SRC := ./src
UNIT_TESTS := ./unit_tests

# Ключи компиляции программы
CFLAGS := -Wall -Wextra -Wpedantic -Werror -std=c99  -I $(INC) -lm
CHECK_FLAGS := -lcheck 
# Доп ключи -Wfatal-errors -Wvla -lpthread -lrt -lsubunit
#CHECK_FLAGS := -lcheck 

# Все с- файлы
SRCS := $(wildcard $(SRC)/*.c)
SRCS_TEST := $(wildcard $(UNIT_TESTS)/*.c)
IO := $(wildcard $(SRC)/io.c)
UNIT_T := $(wildcard $(UNIT_TESTS)/check*.c)


# Все обьектные файлы для приложения (считывает из папки src все файлы .с 
# и меняет разрешение) $(IO:$(SRC)/%io.c=$(OUT)/%io.o)
OBJS := $(SRCS:$(SRC)/%.c=$(OUT)/%.o)
IO_TEST_OBJ := $(SRCS_TEST:$(UNIT_TESTS)/%_test.c=$(OUT)/%_test.o) $(IO:$(SRC)/io.c=$(OUT)/io.o)
UNIT_TEST_OBJ := $(UNIT_T:$(UNIT_TESTS)/check%.c=$(OUT)/check%.o) $(OUT)/basic.o $(OUT)/alloc.o


# Включения зависимостей


# Компилятор
CC := gcc

app.exe: clean out $(OBJS)
	@$(CC) -o $@ $(OBJS)

unit_tests.exe: clean out $(UNIT_TEST_OBJ)
	@$(CC) -o $@ $(UNIT_TEST_OBJ) $(CHECK_FLAGS) -lm

io_test.exe: clean out $(IO_TEST_OBJ) 
	@$(CC) -o $@ $(IO_TEST_OBJ)

$(OUT)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)/%.o: $(UNIT_TESTS)/%.c 
	@$(CC) $(CFLAGS) -o $@ -c $<  

$(OUT)/%.o: $(UNIT_TESTS)/check%.c
	@$(CC) $(CFLAGS) -o $@ -c $< 

$(OUT)/io.o: $(SRC)/io.c 
	@$(CC) $(CFLAGS) -o $@ -c $< 

$(OUT)/basic.o: $(SRC)/basic.c
	@$(CC) $(CFLAGS) -o $@ -c $< 

$(OUT)/alloc.o: $(SRC)/alloc.c
	@$(CC) $(CFLAGS) -o $@ -c $< 

out:
	@mkdir out

.PHONY: clean delete

clean:
	@rm -f *.exe $(OUT)/*.o
	

delete: 
	rm out/*.o

.DEFAULT_GOAL := app.exe

