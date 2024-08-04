.386
extrn input_array_16:byte
extrn print_out_results:far
unsigned_2_data segment para USE16 'data'
    unsigned_2_array            db      16 DUP(31h, 30h)
    unsigned_2_array_size       =       ($  -  unsigned_2_array)
unsigned_2_data ends

unsigned_2_code segment para USE16 'code'
assume cs:unsigned_2_code, ds:unsigned_2_data
unsigned_2 proc far USES ds es
        mov ax, unsigned_2_data
        mov ds, ax

        xor ax, ax
        xor bx, bx
        xor cx, cx

        mov si, offset unsigned_2_array
        mov bx, 0000 
        mov cl, 16
        read_byte:
                ; xor ax, ax
                ; xlatb  TODOOOOOOOOOO
                mov ax, es:[bx]
                mov dx, 4
                and al, 0Fh                     ; Используем маску 00001111 ,чтобы оставить только последние 4 бита регистра al
                shl al, 4                       ; Сдвигаем влево на 4, чтобы в след цикле оценивать результаты сдвига 
        cycle_shift:
                shl al, 1
                mov byte ptr [si], '0'
                jnc last_zero
                mov byte ptr [si], '1'
        last_zero:
                inc si
                dec dx
                test dx, dx
                jnz cycle_shift
                inc bx
                dec cl
                test cl, cl
                JNZ  read_byte  
        

; Стандартная передача параметров для печати см. файл sgn_8.asm
        mov ax, unsigned_2_data
        mov es, ax
        mov si, offset unsigned_2_array
        mov bl, 4
        mov dh, 4
        mov ch, 16
        call far ptr [print_out_results]
        ret 
unsigned_2 endp
unsigned_2_code ends
end
