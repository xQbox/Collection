CC  	:= g++

INC		:= inc
OUT		:= out
SRC		:= src

# QA		:= /

# ifeq (g++, $(CC))
# 	+CC := g++
# else
# 	+CC := clang
# 	+CFLAGS := -Wall -Wpedantic -Wextra -I (INC)/
# endif


CFLAGS 	:= -Wall -Werror -Wpedantic -Wextra -std=c++17 -I $(INC)/
C_ALL	:= $(wildcard $(SRC)/*.cpp)	

OBJ 	:= $(C_ALL:$(SRC)/%.cpp=$(OUT)/%.o)

app.exe: $(OBJ)
	$(CC) -o $@ $<

$(OUT)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f $(OBJ)/*.o *.exe
