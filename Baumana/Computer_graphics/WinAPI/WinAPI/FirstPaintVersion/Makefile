
# MY project folders  
INC 		:= .\inc
OUT			:= .\out
SRC			:= .\src
DBG			:= .\debug


# Using compiler
CXX 		:=  g++

# Compiling flags 
# -Wpedantic -Werror -Wextra
FLAGS       := -Wall -std=c++14 -I $(INC)\

# Linker flags
# LDFLAGS = -lSDL
LDFLAGS = -lm

# Standart directory path
WINDOWSINC 	:= C:\


# CXX_ALL		:= $(wildcard $(SRC)\*.cpp)
# OBJ			:= $(CXX_ALL:$(SRC)\.cpp=$(OUT)\.obj)


app.exe: $(OUT)\main.obj 
	$(CXX) -o $@ $< -l gdi32 -Wl,-subsystem=3

# If subsystem = 3 its debug version


# debug info 
# $(CXX) -o $@ $< -l gdi32 -Wl,-subsystem=3

# -Wl,-subsystem=2
# -Wl linker option (or -subsystem=windows)
#  C:\Windows\System32\gdi32.dll
# -Wl,-subsystme=3 (-subsystem=-console)
# -l  gdi32


$(OUT)\main.obj: $(SRC)\main.cpp
	$(CXX) $(FLAGS) -o $(OUT)\main.obj -c $<

preproc: $(SRC)\main.cpp
	@$(CXX) -E -o preproc.cpp $< 
	@move preproc.cpp $(DBG) > NUL

info.txt:	
	@objdump -p app.exe > info.txt
	@move info.txt $(DBG) > NUL
# $(OUT)\%.obj: $(SRC)\%.cpp
# 	$(CXX) $(FLAGS) -o $@ -c $(SRC)\%.cpp

# $(OUT)\%.obj:  $(SRC)\%.cpp
# 		$(CXX) $(FLAGS) -o $@ -c $<
 
.PHONY: clean rebuild

clean:
	del $(OUT)\*.obj *.exe

rebuild:
	clean app.exe
