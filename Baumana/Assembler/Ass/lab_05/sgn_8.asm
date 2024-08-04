.386
extrn input_array_16:byte
extrn print_out_results:far
public signed_8
signed_8_data segment para USE16 'data'
    signed_8_array            db      8   DUP(31h,30h)
    signed_8_array_size       =       ($  -  signed_8_array)
    result                    db      4    DUP(0)
    result_size               db      1     
    sign_result               db      0
signed_8_data ends

signed_8_code segment para USE16 'code'
assume cs:signed_8_code, ds:signed_8_data
signed_8 proc far USES ds es

        mov ax, signed_8_data
        mov ds, ax
        xor cx, cx 
        xor ax, ax
        mov si, offset signed_8_array
        mov bx, 0000                            ; Смешение числа (массива) в сегменте данных
        mov cl, 4                               ; Количество разрядов числа (поддерживает перевод до макисмального размера сегмента) 

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
        


; Clean first byte of the number
        mov si, offset signed_8_array
        mov cx, 8
        L1:
            mov byte ptr [si], '0'
            inc si
            loop L1

; Checking sign (strict the 8 position of the number)
        mov bx, offset result
        mov si, offset signed_8_array
        add si, 8
        mov dl, [si]
        cmp dl, 31h
        JE MINUS
        mov al, 2Bh
        mov [bx], al
        jmp algorithm_result


; Алгоритм инвертирования числа ( перевод  из обычного кода в обратный код ) 
; Invert number from direct code to additional code
        MINUS:
            mov al, 2Dh
            mov [bx], al
            mov si, offset signed_8_array
            mov ch, 7                               ; Задаем количество выполняемых циклов
            mov cl, 0
            mov si, offset signed_8_array_size
            dec si
            xor al, al
            start_inv:
                test ch, ch
                jz next_step
                mov al, [si]
                cmp al, 31h
                je input_zero
                mov al, 31h
                mov [si], al
                dec ch
                dec si
                jmp start_inv
            input_zero:
                mov al, 30h
                mov [si], al
                dec si
                dec ch
                jmp start_inv

; Algorithm adding 1 to number in 2 (number system)
; CH cycle amount
; CL previous result  (starting as 1 to emulate "add 1 to number")
        next_step:
            
; handling the individual case as FF
            ; mov cx, 8
            ; mov si, offset signed_8_array_size
            ; dec si
            ; L3:
            ;     mov al, [si]
            ;     cmp al, 30h
            ;     JNE adelante        
            ;     loop L3

            mov si, offset signed_8_array
            add si, 8
            mov al, 31h
            mov [si], al
        
        adelante:
            mov ch, 7                                ; Задаем количество выполняемых циклов
            mov cl, 31h                              ; Simulation adding 1 to our number
            mov si, offset signed_8_array_size
            dec si
            xor al, al
        
        start_add:    
            test ch, ch 
            jz overflow_check
            mov al, [si]
            cmp al, 31h
            je flag_
            jmp result_register

        flag_:
            cmp cl, 31h
            jne input_1
            mov al, 30h
            mov [si], al
            mov cl, 31h
            dec si
            dec ch
            jmp start_add

        result_register:
            cmp cl, 30h
            je set_zero
        
        input_1:
            mov al, 31h
            mov [si], al
            mov cl, 30h
            dec si
            dec ch
            jmp start_add

        set_zero:
            mov al, 30h
            mov [si], al
            mov cl, 30h
            dec si
            dec ch
            jmp start_add


; Handling the case with MINUS MAXIMUM SIZE
; Overflow_check applied only one time after the main cycle
        overflow_check:
            cmp cl, 31h
            jne algorithm_result
            mov bx, offset result
            inc bx
            mov al, 32h
            mov [bx], al
            inc bx 
            mov cx, 2
            mov al, 30h
            L4:
                mov [bx], al
                inc bx
                loop L4
            jmp go 


            ; mov si, offset signed_8_array_size 
            ; dec si
            ; mov al, 31h
            ; mov [si], al
            




        algorithm_result:   
            mov ch, 2                               ; Задаем количество выполняемых циклов
            mov cl, 0
            mov si, offset signed_8_array_size
            dec si
            mov bx, offset result_size
            dec bx
            xor al, al

; ; Алгоритм перевода в знаковую 8 с/с из беззнаковой 2 с/с (работает строго, если кол-во элементов в 2с/с mod3 = 1 ) 
        start:
            mov dl, [si]
            cmp dl, 30h
            JE  null_
            inc cl
            dec si 
            cmp cl, 1
            JE add_1
            cmp cl, 2
            JE add_2
            add al, 4
            jmp oct_
        add_1:
            add al, 1
            jmp start
        add_2:
            add al, 2
            jmp start
        null_:
            dec si
            inc cl
            cmp cl, 3
            JE oct_
            jmp start
        oct_:
            mov cl, 0h
            add al, 30h
            mov [bx], al
            xor al, al
            dec bx
            dec ch 
            cmp ch, 0h
            JE next_                        ; Условие выхода из цикла, задается в регистре ch 
            jmp start 
   
 

; ; Анализ знака числа (анализирует фиксированную позицию (8) )
;         sign_:
;             mov bx, offset result
;             mov si, offset signed_8_array
;             add si, 8
;             mov dl, [si]
;             cmp dl, 31h
;             JE minus
;                 mov al, 2Bh
;                 mov [bx], al
;                 jmp next_ 
;             minus:
;                 mov al, 2Dh
;                 mov [bx], al

; ; Анализирует последнюю тройку после алгоритма перевода
        next_:
            mov bx, offset result
            mov si, offset signed_8_array
            add si, 8
            inc si 
            inc bx
            mov dl, [si]
            cmp dl, 31h
            JE one_prnt 
            mov dl, 30h
            mov [bx], dl
            jmp go


        one_prnt:
            mov dl, 31h
            mov [bx], dl

        go:
        mov ax, signed_8_data   ; параметр старта печати
        mov es, ax  
        mov si, offset result   ; параметр старта печати (es:[si])
        mov bl, 4               ; 
        mov dh, 4               ; параметр разрядности
        mov ch, 4               ; параметры выставления точки
        call far ptr [print_out_results]
        ret 
signed_8 endp
signed_8_code ends
end
