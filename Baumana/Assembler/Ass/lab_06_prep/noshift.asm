.model tiny
.286
.code 
        alt_key             equ     08h     ; бит 3 равен 1
        ctrl_key            equ     04h     ; бит 2 равен 1
        keyboard_port       equ     60h     ; порт клавиатуры
        del_key             equ     53h       ; Скан код или Аски код для обработки нажатия клавиши w
        rt_shift            equ     01h
        org  100h
main:
        mov ax, 3508h
        int 21h
; es:bx  is now pounter to interrupt


; STEP 2: Make another interrupt behave like int 8
; We do this by pointing another interrupt at the vectror for int8
; int 21, 25
; Set DS:DX to the desired vector point, set AL to interrupt number;
; 
        mov dx, bx
        mov ax, es
        mov ds, ax
; Now DS:DX equals whatever ES:BX was
        mov al, 0C8h        ; address of interrupt in interrupts table
        mov ah, 25h
        int 21h
; interrupt C8 now points to the code location of INT 8.

; STEP 3 : Set Int8 s vector to my own TSR routine
; Need to set DS:DX to point to "MYTSRCODE"
        mov ax, cs
        mov ds, ax
        mov dx, offset MYTSRCODE
        mov al, 8h
        mov ah, 25h     ; Set interrupt vector point
;
; Step 4: do int 21, 31 and done
        mov al, 0
        mov dx, 4       ; How much memory is reserved for TSR
        mov ah, 31h     ; Make this into a TSR
        int 21h  

MYTSRCODE:
        cli         ; disable interrupts
        pusha       ; preserves AX, BX, CX, etc, except ds
        push ds      

; Here what we can do
; Change th third bit of memory location 40:17 to be zero.
        mov ax, 40h
        mov ds, ax
        mov bx, 17h
        mov ax, [bx]
        and ax, 11111101b
        mov [bx], ax
; DONE !



        pop ds       ; restore pop
        popa
        int 0c8h    ; do the old int 8h
        push ax
        mov al, 20h
        out 20h, al         ; sends an End-Of-Interrupt controller
        pop ax
        sti         ; Enable hardware interrupts
        iret



end main

