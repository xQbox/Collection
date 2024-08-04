SRC			:= .\src
OUT			:= .\out
INC			:= .\inc

CC			:= clang

C_FLAGS		:= -Wall -I $(SRC)\

ASMx86_FLAG	:= -S -mllvm --x86-asm-syntax=intel	
# C_ALL		:= $(wildcard $(SRC)\*.c)

OBJ			:= $(C_ALL:$(OUT)\*.o=$(SRC)\*.c)

app.exe: $(OUT)\main.o $(OUT)\copyString.obj
	$(CC) -o $@ $(OUT)\main.o $(OUT)\copyString.obj

# -fuse-ld=lld or link or link-lld (Using linker)
#$(OUT)\copyString.o

$(OUT)\main.o:	$(SRC)\main.c
	$(CC) $(C_FLAGS) -o $@ -c $(SRC)\main.c

$(OUT)\copyString.obj: $(SRC)\copyString.asm
	ml64.exe /c $(OUT)\copyString.obj $(SRC)\copyString.asm
	move copyString.obj .\out\


.PHONY: clean

clean: 
	del $(OUT)\*.o *.exe