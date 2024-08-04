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
        mov ah , 0
        int 16h
        cmp ah, 1   ; 1 is scan code for the Escape key
        JE ender
; AH containc scan code of the pressed key, and AL is the ASCII code
; Print pressed key
        mov ah, 0Eh         ; write characters at current cursor position
        mov bx, 0           ; page to output
        mov bl, 7           ; Graphics mode only
        mov cx, 1           ; just print one character

        int 10h
    JMP begin   
    ender:
        mov ax, 4C00h
        int 21h 
end main

