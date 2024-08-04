
.386
public input_unsigned_16
i_data segment para USE16 'data'
    public input_array_16
    input_array_16          db      4 DUP(0Ah, 0Bh, 0Ch, 0Dh)
    input_array_size        =       ($ - input_array_16)
    input_array_msg         db      13, 10, 'Input your number below: ', 13, 10, '>> ', '$'
i_data ends

i_code segment para USE16 'code'
assume cs:i_code, ds:i_data
input_unsigned_16 proc far USES ds 
; Read number from keyboard (ONLY AVAILABLE [30h, 39h] && [41h, 46h])
; CX - quantity of readed bytes
        mov ax, i_data
        mov ds, ax
        mov es, ax
        mov ah, 09h
        mov dx, offset input_array_msg
        int 21h
        mov ah, 01h
        mov cx, 4h
        mov si, offset input_array_16
        array_read:
            int 21h
            cmp al, 40h
            JA A_
            cmp al, 30h
            JB array_read
            sub al, 30h
            jmp B_
        A_:
            cmp al, 46h
            JA array_read
            sub al, 37h
        B_:
            mov [si], al
            inc si
            loop array_read
    ret
input_unsigned_16 endp
i_code ends
end
