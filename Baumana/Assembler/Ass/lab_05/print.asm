.286
stack segment para USE16 stack 'stack'
    _stack              db   100h   DUP('STACK+++')
stack ends
data segment para USE16 'data'
    interruption_address        word    ?, ?
    try_msg                     db      'Hello, world', '$'
    string                      db      'HELLO<<I AM<<ALEX'
    color_black                 db       00001000b;00001111 белый цвет(black shl 4) OR blue
    color_blue                  db       00000001b;               
    color_attribute              =       10000000b
data ends

; hot_key equ '' 
code segment para USE16 'code'
; assume ds:data, cs:code, ss:stack
main:
    mov ax, data
    mov ds, ax
    mov dx, 4
    mov ah, 01h
    int 21h
    in al, 60h
    cmp al, 33h
    JNE out_message
    call tsr_prog_start
out_message:
    mov dl, 13
    mov ah, 02h
    int 21h
    mov dl, 10
    int 21h
    mov dl, 36h
    int 21h
    mov ax, 4C00h
    int 21h
    ; push ax
    ; push dx
    ; mov dx, 03DAh ; Порт регистра ISR1.
    ; wait_retrace_end:
    ;     in al, jfsa;l dx
    ;     test al, 1000b ; Проверить бит З.
    ;     ; Если не ноль -
    ;     jnz wait_retrace_end ; подождать конца текущего обратного хода,
    ; wait_retrace_start:
    ;     in al, dx
    ;     test al,1000b ; а теперь подождать начала следующего.
    ;     jz wait_retrace_start
    ; pop dx
    ; pop ax
   
    ; mov ah, 03h
    ; mov bh, 0
    ; int 10h
    ; push dx 

    ; mov ah, 02h
    ; mov dh, 5h
    ; mov dl, 6h
    ; mov bh, 0
    ; int 10h

    ; mov ah, 09h
    ; mov dx, offset try_msg
    ; int 21h 
    
    ; pop dx
    ; mov ah, 02h
    ; mov bh, 0
    ; int 10h

    ; mov ah, 09h
    ; mov bh, 0
    ; mov al, 33h
    ; mov bl, 101b
    ; mov cx, 2
    ; int 10h

    ; mov ah, 03h
    ; mov al, 06h
    ; int 10h

    ; mov ah, 01h
    ; int 21h
; INT 10h, АН = 03h: Считать положение и размер курсора
; Вход: АН = 03h
; ВН = номер страницы
; Выход: DH, DL = строка и столбец текущей позиции курсора
; СН, CL = первая и последняя строки курсора

; Вход: АН = 02h
; ВН = номер страницы
; DH = строка
; DL = столбец
    ; mov ax, 0003h
    ; int 10h
;     INT 10h, АН = OOh: Установить видеорежим
; Вход: АН = OOh
; AL = номер режима в младших 7 битах
    ; mov bh, 0INT 10h, АН - 09h: Вывести символ с заданным атрибутом на экран
; Вход: АН = 09h
; ВН = номер страницы
; AL = ASCII-код символа
; BL = атрибут символа
; СХ = число повторений символа
    ; mov dl, 20h
    ; mov dh, 20h
    ; mov ah, 02h
    ; int 10h
    ; pop bp
    ; mov ah, 0Eh
    ; mov bh, 0h
    ; mov al, 33h
    ; int 10h

    ; mov ah, 09h
    ; mov dx, offset try_msg
    ; int 21h
;     pusha
;     xor bx, bx
;     mov bx, dx
;     lea ax, [bx]
;     shl ax, 4
;     push cx
;     shr cx, 3
;     add ax, cx
;     mov di, ax
;     pop cx
;     and cx, 07h
;     mov bx, 0080h
;     shr bl, cl
;     mov dx, 03ECh
;     mov ax, 0F01h
;     out dx, ax
;     mov al, 08
;     mov ah, bl
;     out dx, ax
;     mov ah, byte ptr es:[di]
; ;
;     mov byte ptr es:[di], ah
; ;
;     popa
    ; ret





tsr_prog_start proc far uses ax bx cx dx  
    mov ah, 01h
    int 21h
    in al, 60h
    cmp al, 33h
    JNE return_managment

; Очистка экрана
    mov ax, 0003h
    int 10h

; Печать символа 
    mov ah, 02h
    mov dh, 5h
    mov dl, 6h
    mov bh, 0
    int 10h

; Очистка
    mov ax, 0003h
    int 10h

; Печать строки в режиме эмуляции телетайпа
    
    ; mov ax, data
    ; mov es, ax
    ; mov ah, 13h
    ; mov al, 03h
    ; mov bh, 0
    ; mov cx, (sizeof string_color) / 2
    ; mov dh, 4
    ; mov dl, 4
    ; push bp
    ; mov bp, offset string_color
    ; pop bp
    ; int 10h
; Очистка
    ; mov ax, 0003h
    ; int 10h
; Печать цветной строки на экран
    mov ax, data
    mov es, ax
    call  EnableBlinking
    mov cx, sizeof string
    mov si, offset string
    mov dx, 0
    L1:
        push cx
        mov ah, 9
        mov al, [si]
        mov bh, 0
        cmp dx, 0
        JE blue
        mov bl, es:color_black
        or bl, color_attribute
        dec dx
        jmp adelante
blue:
        mov bl, es:color_blue
        or bl, color_attribute
        inc dx
adelante:
        mov cx, 1
        int 10h
        mov cx, 1
        call Cursor
        ; inc color 
        inc si
        pop cx
        loop L1
    

return_managment:
    mov ah, 02h
    mov dl, 33h
    int 21h

    ret
tsr_prog_start endp

Cursor proc near uses ax bx cx dx
    L2:
        push cx
        mov ah, 3
        mov bh, 0
        int 10h
        inc dl
        mov ah, 2
        int 10h
        pop cx
        loop L2
        ret
Cursor endp
EnableBlinking proc near uses ax bx cx dx 
    mov ax, 1003h
    mov bl, 1 ; 0 выключить мигание
    int 10h
    ret
EnableBlinking endp
code ends
end main

