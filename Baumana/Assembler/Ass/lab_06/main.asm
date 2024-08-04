.model tiny
.186
.code 
        alt_key             equ     08h     ; 3-rd bit equals 1
        shift_key           equ     02h     ; 1-st bit equals 1
        keyboard_port       equ     60h     ; Keyboard port
        org  100h
main:
    jmp setup
    

MyKeyboardInterrupt:
    
; Save register which was changed (without also work)
    push ax
    push es             ;if uncomment this line it will be print 2 times SCAN-CODE ','
    push di

; Check for EnableKey set
    mov bx, offset EnableKey
    mov al, [bx]
    cmp al, 0
    je MODE

; prohibid interrupts
   cli

; Read key directly from Keyboard port
    in al, 60h

; If F2 (or scan-code other key "") pressed switch to normal mode, else print in SCAN-CODE-MODE 
    cmp al, 3Ch                 ; for other HOT-Key change here
    je NORMAL_MODE
     
    mov byte ptr KeyBuffer, al

; Print SCAN-CODE placed in KeyBuffer 
; CX - quantity of printing symbols
; BH - output page
; BL - foreground pixel color (only in graphics mode)
    mov al, byte ptr KeyBuffer
    mov ah, 0Eh
    mov cx, 1
    mov bh, 0
    mov bl, 7
    int 10h


;     in al, 61h
;     mov ah, al                      ; store the original value of AH
;     or al, 80h                      ; force the first 1 bit to al
;     out 61h, al
;     mov al, ah
;     out 61h, al                     ; send the original value back
    
  
;     mov al, 20h
;     out 20h, al                     ; Sends the end-of-interrupt signal to the 8259 (programer interrupt controller) (PIC)


;     pop di
;     pop es
;     pop ax
; ; Allow the system interrupts
;     sti     
;     iret
; Posible way to setup EnableKey
; Read Hot-Keys for setup Mode
; In SCAN-CODE-MODE NO BUFFER (BUFFER = 1) 
    MODE:

; Read special keys directly from PC memory address (40:17)
        mov ax, 40h
        mov es, ax 
        mov di, 17h


; If AH == 08h (ALT pressed mask) ZF = 0 is unset else ZF = 1
        mov ah, es:[di]
        and ah, 08h
        jz standart_out


; If AH == 02h (Left shift pressed mask) ZF = 0 is unset else ZF = 1
        mov ah, es:[di]
        and ah, 02h
        jz standart_out

; Setup EnableKey to SCAN-CODE-MODE
        mov al, 1
        mov byte ptr EnableKey, al        
        jmp standart_out

; Setup EnableKey to NORMAL_MODE
    NORMAL_MODE:
        mov al, 0
        mov byte ptr EnableKey, al
        

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


; DS:DX needs to point to the new interrupt routine 
        push cs         ; push the code segment ...
        pop ds          ; to make ds equal this routine s code segment
        mov dx, offset MyKeyboardInterrupt
        mov al, 9       ; keyboard handler
        mov ah, 25h
        int 21h

; End program like a TSR
; DX value is size in "para" (16 bytes) for TSR part 
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
        
end main


