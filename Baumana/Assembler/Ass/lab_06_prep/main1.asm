.model tiny
.186
.code 
        alt_key             equ     08h     ; бит 3 равен 1
        ctrl_key            equ     04h     ; бит 2 равен 1
        keyboard_port       equ     60h     ; порт клавиатуры
        del_key             equ     53h       ; Скан код или Аски код для обработки нажатия клавиши w
        rt_shift            equ     01h
        org  100h
main:
; key pressed
begin:
        mov ah, 1
        int 16h
        jz begin
        
        cmp ah, 1   ; 1 is the 
        je ender

        mov ah, 0Eh
        mov bh, 0;
        mov bl, 7
        mov cx, 1
        int 10h
        jmp begin

    ender:
        mov ax, 4C00h
        int 21h
        
         
end main

