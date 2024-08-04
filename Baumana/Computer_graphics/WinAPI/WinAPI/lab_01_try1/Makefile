
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



##### NEED TO ADD BEFORE DEBUG BUILD!!! 
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

##### Correct Debug build
# app.exe:	$(OUT)\main.obj
# 	clang-cl  -fuse-ld=lld -fsanitize=address -v  -o app.exe $(OUT)\main.obj 

# -fuse-ld=lld or link or link-lld (Using linker)

# /Zi "E:\LLVM\lib\clang\11.0.0\lib\windows\clang_rt.asan_cxx-x86_64.lib" "E:\LLVM\lib\clang\11.0.0\lib\windows\clang_rt.asan-x86_64.lib"
# /Zi "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\lib\clang\17\lib\windows\clang_rt.asan_cxx-i386.lib" "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\lib\clang\17\lib\windows\clang_rt.asan-i386.lib"

##### Release build
app.exe: $(OUT)\main.obj 
	$(CXX)  -o $@ $< -l gdi32 -Wl,-subsystem=3


# app.exe: $(OUT)\main.obj  $(OUT)\clang_rt.asan-x86_64.obj 
# 	cl.exe -fsanitize=address  /LIBPATH:$(SRC)\clang_rt.asan-x86_64.lib -o $@ $< 



#  /DEFAULTLIB "E:\LLVM\lib\clang\11.0.0\lib\windows\clang_rt.asan_dynamic-x86_64.dll"
# set ASAN_OPTIONS= windows_hook_rtl_allocators=true



# app.exe: $(OUT)\main.obj 
# 	clang-cl -fsanitize=address /Zi -o app.exe  $(OUT)\main.obj 





#   /LIBPATH:E:\LLVM\lib\clang\11.0.0\lib\windows\ /MT "E:\LLVM\lib\clang\11.0.0\lib\windows\clang_rt.asan-x86_64.lib" /MT E:\LLVM\lib\clang\11.0.0\lib\windows\clang_rt.asan_dynamic-x86_64.lib -o app.exe $(OUT)\main.obj

# /DLL E:\LLVM\lib\clang\11.0.0\lib\windows\clang_rt.asan_dll_thunk-x86_64.dll
# /LIBPATH:E:\LLVM\lib\clang\11.0.0\lib\windows /DEFAULTLIB:E:\LLVM\lib\clang\11.0.0\lib\windows\clang_rt.asan-x86_64.lib 
# If subsystem = 3 its debug version
# /DEFAULTLIB "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.39.33519\bin\Hostx64\x64\clang_rt.asan_dynamic-x86_64.dll"

# debug info 
# $(CXX) -o $@ $< -l gdi32 -Wl,-subsystem=3

# -Wl,-subsystem=2
# -Wl linker option (or -subsystem=windows)
#  C:\Windows\System32\gdi32.dll
# -Wl,-subsystme=3 (-subsystem=-console)
# -l  gdi32



##### Release build with g++ compiler
$(OUT)\main.obj: $(SRC)\main.cpp
	$(CXX) $(FLAGS) -o $(OUT)\main.obj -c $< 


##### Correct Debug build
# $(OUT)\main.obj: $(SRC)\main.cpp
# 	clang-cl -fsanitize=address  -o $(OUT)\main.obj -c $< 



#"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\lib\clang\17\lib\windows\clang_rt.asan_cxx-i386.lib" "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\lib\clang\17\lib\windows\clang_rt.asan-i386.lib" 




# $(OUT)\main.obj: $(SRC)\main.cpp
# 	cl.exe -fsanitize=address "E:\LLVM\lib\clang\11.0.0\lib\windows\clang_rt.asan-x86_64.lib" -o $(OUT)\main.obj -c $<  


# $(OUT)\main.obj: $(SRC)\main.cpp
# 	cl.exe -fsanitize=address "E:\LLVM\lib\clang\11.0.0\lib\windows\clang_rt.asan-x86_64.lib" -o $(OUT)\main.obj -c $<  

# # set CL= /fsanitize=address /GS- /wd5072 & set LINK= /InferASanLibs /incremental: нет /debug

# $(OUT)\main.obj: $(SRC)\main.cpp 
# 	cl -fsanitize=address  -o $(OUT)\main.obj -c $<


# $(OUT)\clang_rt.asan-x86_64.obj: $(SRC)\clang_rt.asan-x86_64.lib
# 	clang  -fsanitize=address -o $(OUT)\clang_rt.asan-x86_64.obj -c $(SRC)\clang_rt.asan-x86_64.lib


# -O0 -g -fno_omit_frame-pointer -fsanitize=address

# Rc compiler not working TODO
# $(OUT)\menudemo.obj:	$(SRC)\menudemo.rc  $(INC)\menudemo.h
# 	GoRC.exe /r $(SRC)\menudemo.rc
# 	GoRC.exe /r $(SRC)\menudemo.res > $(OUT)\menudemo.obj
	
# GoRC.exe /r $(SRC)\menudemo.res
	

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



# cl /I C:\"Program Files (x86)"\"Windows Kits"\10\Include\10.0.22000.0\um 
# /I C:\"Program Files (x86)"\"Windows Kits"\10\Include\10.0.22000.0\shared
# /I C:\"Program Files"\"Microsoft Visual Studio"\2022\Community\VC\Tools\MSVC\14.39.33519\include 
# /I C:\"Program Files (x86)"\"Windows Kits\10"\Include\10.0.22621.0\ucrt 
# main.cpp -fsanitize=address /Zi