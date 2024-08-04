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
        mov ah, 12h
        int 16h

        and ah, 1    ; If last bit of AH is 1
        jz begin

        mov ah, 0Eh     ; Write text in teletype mode
        mov al, 41h     ; A
        mov cx, 1       ; number of charachters to write
        mov bh, 0
        mov bl, 7
        int 10h

        jmp begin  
end main

