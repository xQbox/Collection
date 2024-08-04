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
    jmp setup 

MYTSRCODE proc far
        sti         ; disable interrupts
        pusha       ; preserves AX, BX, CX, etc, except ds
        push ds      
        
; Here what we can do
        
        
        in al, 60h
        cmp al, 3Fh
        JNE default_interrupt
; Hot key pressed
        
        mov dx , 3c8h
        mov al, 0
        out dx, al
        
        mov dx, 3c9h
        mov al, 0
        out dx, al

        mov al, 35
        out dx, al

        mov ax, 0A000h
        mov es, ax
        
        mov cx, 10
        mov di, 35000
        
        DrawPixel1:
            mov byte ptr es:[di], 1
            add di, 5
            loop DrawPixel1

        
        cli 
        in al, 61h
        or al, 80h
        out 61h, al
        and al, 7Fh
        out 61h, al
        mov al, 20h
        out 20h, al
        sti 
        pop ds
        popa
        iret
    
; No hot key was pressed
default_interrupt:
        pop ds
        popa 
        cli
        pushf
        call cs:old_interrupt_9
        iret



; DONE !
        old_interrupt_9     dw      ?

MYTSRCODE endp
        
end_tsr label byte 

setup:
        ; mov ah, 0           ; Set the videomode 
        ; mov al, 13h         ; 320x200 VGA
        ; int 10h
        ; cli
        mov ax, 3509h
        int 21h
; es:bx  is now pounter to interrupt


; STEP 2: Make another interrupt behave like int 8
; We do this by pointing another interrupt at the vectror for int8
; int 21, 25
; Set DS:DX to the desired vector point, set AL to interrupt number;
; 
        mov word ptr old_interrupt_9, bx
        mov word ptr old_interrupt_9 + 2, es
        ; mov ds, ax
; Now DS:DX equals whatever ES:BX was
        mov al, 9h        ; address of interrupt in interrupts table
        mov ah, 25h
        mov dx, offset end_tsr
        int 21h

; interrupt C8 now points to the code location of INT 8.

; STEP 3 : Set Int8 s vector to my own TSR routine
; Need to set DS:DX to point to "MYTSRCODE"
        ; mov ax, cs
        ; mov ds, ax
        ; mov dx, offset MYTSRCODE
        ; mov al, 9h
        ; mov ah, 25h     ; Set interrupt vector point
;
; Step 4: do int 21, 31 and done
    
        mov dx, offset end_tsr
        shr dx, 4
        inc dx
        mov ah, 31h     ; Make this into a TSR
        int 21h  
end main

