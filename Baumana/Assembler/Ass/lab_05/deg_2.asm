.386
extrn input_array_16:byte
public degree_of_two
degree_of_two_data segment para USE16 'data'
    degree_of_two_array         db      8   DUP(31h,30h)
    degree_of_two_result        db      20h, 20h
degree_of_two_data ends

degree_of_two_code segment para USE16 'code'
assume cs:degree_of_two_code, ds:degree_of_two_data
degree_of_two proc far USES ds 
        mov ax, degree_of_two_data
        mov ds, ax
        xor cx, cx          
        ; mov ah, 3
        ; mov al, 5
        ; rcl ax, 1 
        xor ax, ax
        mov si, offset degree_of_two_array
        mov bx, 0000            ; Смешение числа (массива) в сегменте данных
        mov cl, 4               ; Количество разрядов числа (поддерживает перевод до макисмального размера сегмента) 
; Алгоритм перевода числа N (количество чисел задается в cl) в 16 ричной с/с в беззнаковую двоичную. 
        read_byte:
            mov ax, es:[bx]
            mov dx, 4
            and al, 0Fh
            shl al, 4
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
        
        mov ah, 02h  
        mov dl, 13
        int 21h
        mov dl, 10
        int 21h

    
; Алгоритм поиска максимальной степени двоики    
        mov si, offset degree_of_two_result
        mov dl, 30h
        dec si
        mov al, 0
        mov bx, offset degree_of_two_result
        mov cx, 16
     
        start:
            cmp dl, [si]
            JE add_degree
            jmp go
            loop start
        add_degree:
            inc al      
            dec si  
            dec cx
            jmp start
        go:
            cmp al, 16
            JE bad_result
            cmp al, 9
            JA more_than_ten 
            add al, 30h                              ; Если степень двойки меньше 10
            mov ah, 02h
            mov dl, al
            int 21h
            jmp out_from

        bad_result:
            mov dl, 30h
            mov ah, 02h
            int 21h 
            jmp out_from
            
        more_than_ten:                               ; Условие если степень двойки больше 10
            mov si, offset degree_of_two_result
            mov ah, 31h 
            mov [si], ah
            add al, 26h                             ; Добавляем 26 (с учетом текущей разницы al и представлением цифр в ASCII)     
            inc si                                  ; стандартно 30h , но в al уже лежит число больше 10 
            mov [si], al
            mov si, offset degree_of_two_result
            mov ah, 02h
            mov cx, 2
            loop1:
                mov dl, [si]
                int 21h 
                inc si
                loop loop1
    out_from:
    ret
degree_of_two endp
degree_of_two_code ends
end
