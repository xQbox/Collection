SRC			:= .\src
OUT			:= .\out
INC			:= .\inc

CC			:= clang

C_FLAGS		:= -Wall -I $(INC)\

ASMx86_FLAG	:= -S -mllvm --x86-asm-syntax=intel	
# C_ALL		:= $(wildcard $(SRC)\*.c)

OBJ			:= $(C_ALL:$(OUT)\*.o=$(SRC)\*.c)

app.exe: $(OUT)\main.o $(OUT)\method.o $(OUT)\GetAssemblerTime.obj
	$(CC) -o $@ $(OUT)\main.o $(OUT)\method.o $(OUT)\GetAssemblerTime.obj 

# -fuse-ld=lld or link or link-lld (Using linker)
#$(OUT)\copyString.o

$(OUT)\main.o:	$(SRC)\main.c
	$(CC) $(C_FLAGS) -o $@ -c $(SRC)\main.c

$(OUT)\method.o:	$(SRC)\method.c
	$(CC) $(C_FLAGS) -o $@ -c $(SRC)\method.c

$(OUT)\GetAssemblerTime.obj: $(SRC)\GetAssemblerTime.asm
	ml64.exe /c $(OUT)\GetAssemblerTime.obj $(SRC)\GetAssemblerTime.asm
	move GetAssemblerTime.obj .\out

.PHONY: clean

clean: 
	del $(OUT)\*.o *.exe $(OUT)\*.obj