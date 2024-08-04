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
    ;     out 20h, al                     ; Sends the end-of-interrupt signal to the 8259 (programer interrupt controller) (PIC)
        
    ;     pop ax
    ;     standart_interrupt:
           
        
    ;     sti                             ; turn on the interrupt                           
    ;     iret


; Read pressed key from keyboard port
    ; in al, 60h
    ; mov byte ptr KeyBuffer, al

; Save in AH flags condition
    ; lahf 
    ; cmp al, 33h             ; Scan-code ','
    ; JNE standart_out 

; Read flags condition
    ; sahf

    


; Save register which was changed (without also work)
    push ax
    push es             ;if uncomment this line it will be print 2 times SCAN-CODE ','
    push di

; Read special keys directly from PC memory address (40:17)
    mov ax, 40h
    mov es, ax 
    mov di, 17h

; If AH == 04h (CTRL pressed mask) ZF = 0 is unset else ZF = 1 
    ; mov ah, es:[di]
    ; and ah, 04h
    ; jnz SET_NORMAL_MODE          ; jump to check condition SCAN_CODE_MODE


; If AH == 08h (ALT pressed mask) ZF = 0 is unset else ZF = 1
    mov ah, es:[di]
    and ah, 08h
    jz standart_out


; If AH == 02h (Left shift pressed mask) ZF = 0 is unset else ZF = 1
    mov ah, es:[di]
    and ah, 02h
    jz standart_out

; If Left Shift and Alt pressed
; Switch to SCAN-CODE-MODE
    ; mov byte ptr EnableKey, 1
    ; jmp check_mode

    ; SET_NORMAL_MODE:
    ;     mov byte ptr EnableKey, 0

; Read key value for switch to SCAN-CODE-MODE  
    ; check_mode:
    ;     mov bx, offset EnableKey
    ;     mov al, [bx]
    ;     cmp al, 0
    ;     je  standart_out



; Read key from keyboard port
    in al, 60h
    ; cmp al, 33h
    ; je standart_out
    mov byte ptr KeyBuffer, al


; Print SCAN-CODE AL
    mov al, byte ptr KeyBuffer
    mov ah, 0Eh
    mov cx, 1
    mov bh, 0
    mov bl, 7
    int 10h


    ; in al, 61h
    ; mov ah, al                      ; store the original value of AH
    ; or al, 80h                      ; force the first 1 bit to al
    ; out 61h, al
    ; mov al, ah
    ; out 61h, al                     ; send the original value back
    
  
    ; mov al, 20h
    ; out 20h, al                     ; Sends the end-of-interrupt signal to the 8259 (programer interrupt controller) (PIC)


    ; pop di
    ; pop es
    ; pop ax
    ; iret

    ; pop es         ;if uncomment this line it will be print 2 times SCAN-CODE ','
    ; pop ax
    ; iret

    standart_out:
        pop di
        pop es         ;if uncomment this line it will be print 2 times SCAN-CODE ','
        pop ax
        jmp dword ptr CS:Interrupt_09 
        
    KeyBuffer               db              0                       ; Readed scan-code
    EnableKey               db              0                       ; Enable key for switch output version
    Interrupt_09            dword           ?                       ; Address of standart interrupt
    
    Install_Marker          db              'U'                     ; Residental flag
    StartMessage            db              '>> TSR program uploaded $'
    StopMessage             db              '>> TSR program closed $' 

    setup:

; ES:BX contains int9h address
        mov ax, 3509h
        int 21h

; Check for residental program
        cmp es:Install_Marker, 'U'
        je stop_resident

; Print Hello Message
        mov dx, offset StartMessage 
        mov ah, 09h
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


stop_resident:

; Program-ender message
        mov dx, offset StopMessage
        mov ah, 09h
        int 21h

; Return old address
        mov dx, word ptr es:Interrupt_09
        mov ds, word ptr es:Interrupt_09 + 2 
        mov ax, 2509h
        int 21h

; Free memory
        mov ah, 49h
        int 21h 

; Program End
        mov ah, 4Ch
        int 21h
        
        ; exit:
        ;     mov dl, '3'
        ;     mov ah, 02h
        ;     int 21h
        ;     mov ax, 4C00h
        ;     int 21h
end main


