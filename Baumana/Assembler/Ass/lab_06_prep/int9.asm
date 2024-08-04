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


MyKeyboardInterrupt:
    ;     cli                             ; turn off interrupts
    ;     push ax                         ; preserve AX
        
    ;     in al, 60h                      ; keyboard input
    ;     mov byte ptr KeyBuffer, al      ; 
    ;     ; cmp al, 33h
    ;     ; JNE standart_interrupt
    ;     ; L2:
    ;     ;     mov bx, offset KeyBuffer
    ;     ;     mov al, [bx]
    ;     ;     mov ah, 0Eh
    ;     ;     mov cx, 1
    ;     ;     mov bh, 0
    ;     ;     mov bl, 7
    ;     ;     int 10h
    ;     ;     jmp L2

    ;     in al, 61h
    ;     mov ah, al                      ; store the original value of AH
    ;     or al, 80h                      ; force the first 1 bit to al
    ;     out 61h, al
    ;     mov al, ah
    ;     out 61h, al                     ; send the original value back
        
    ;     ; call Interrupt_09
    ;     mov al, 20h
    ;     out 20h, al                     ; Sends the end-of-interrupt signal to the 8259 (programmer interrupt controller) (PIC)
        
    ;     pop ax
    ;     standart_interrupt:
           
        
    ;     sti                             ; turn on the interrupt                           
    ;     iret

    in al, 60h
    cmp al, 33h
    JNE standart_out
    mov al, [bx]
    mov ah, 0Eh
    mov cx, 2
    mov bh, 0
    mov bl, 7
    int 10h
    standart_out:
        jmp dword ptr CS:Interrupt_09 
        
    ; KeyBuffer  db  0                    ; readed scan-code

    Interrupt_09 dword ?               ; address of standart interrupt


    setup:
; ES:BX contains int9h address
        mov ax, 3509h
        int 21h

; Save the address of 9 (IRQ1) interrupt
        mov word ptr Interrupt_09, bx
        mov word ptr Interrupt_09 + 2, es

; ; Check for correct address
;         xor bx, bx
;         mov ax, 0
;         mov es, ax
;         mov bx, word ptr Interrupt_09
;         mov es, word ptr Interrupt_09 + 2
        

; DS:DX needs to point to the new interrupt routine 
        push cs         ; push the code segment ...
        pop ds          ; to make ds equal this routine s code segment
        mov dx, offset MyKeyboardInterrupt
        mov al, 9       ; keyboard handler
        mov ah, 25h
        int 21h


; We just hijacked int 9

        ; L1:
        ;     mov bx, offset KeyBuffer
        ;     mov al, [bx]
        ;     cmp al, 1
        ;     JE exit
        ;     mov ah, 0Eh
        ;     mov cx, 1
        ;     mov bh, 0
        ;     mov bl, 7
        ;     int 10h
        ;     jmp L1

; End program like a TSR
; DX value is size in para for TSR part 
        mov ax, 3100h
        mov dx, offset setup
        shr dx, 4
        inc dx
        int 21h

        ; exit:
        ;     mov dl, '3'
        ;     mov ah, 02h
        ;     int 21h
        ;     mov ax, 4C00h
        ;     int 21h
end main

