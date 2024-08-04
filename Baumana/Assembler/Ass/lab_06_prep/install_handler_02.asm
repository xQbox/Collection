.286
stack segment para USE16 stack 'stack'
    _stack              db   100h   DUP('STACK+++')
stack ends
data segment para USE16 'data'
    interruption_address        word    ?, ?
    string                      db      'HELLO<<I AM<<ALEX', '$'
    color_black                 db       00001000b;00001111 белый цвет(black shl 4) OR blue
    color_blue                  db       00000001b;               
    color_attribute              =       10000000b
    msg                         db      'Privet Mir', '$'
data ends

; hot_key equ '' 
code segment para USE16 'code'
assume ds:data, cs:code, ss:stack
main:
    mov ax, data
    mov ds, ax
    mov dx, offset string
    mov ah, 09h
    int 21h
install_handler:
    push ds
    mov ax, code
    mov ds, ax
    mov ah, 25h
    mov al, 02h
    mov dx, offset break_handler
    int 21h
    pop ds
    L1:
        mov ah, 1
        int 21h
        int 2h
        cmp al, 33h
        jnz L1


    mov ax, 4C00h
    int 21h
break_handler proc 
    push ax
    push ds
    push dx 
    mov ax, data
    mov ds, ax
    mov dx, ds:offset msg
    mov ah, 09h
    int 21h
    pop dx
    pop ds
    pop ax
    iret
break_handler endp
code ends
end main

