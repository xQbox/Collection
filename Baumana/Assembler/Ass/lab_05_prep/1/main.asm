.386
stack segment para USE16 stack 'stack'
    stack_data      db      100h DUP('STACK+++') 
stack ends

; data_common segment para USE16 'data'
;     new_line1        db      13, 10, '$'
;     input_line1      db      13, 10, '>x ', '$'
; data_common ends
; common_data segment USE16 'data'
; common_data ends

menu_data segment USE16 'data'
    new_line        db      13, 10, '$'
    input_line      db      13, 10, '>> ', '$'
    array           db      16 DUP(0Ah, 0Bh, 0Dh, 0Fh) 
    buff            db      32 DUP(?), '$'
    point           db      '.'
    input_array     db      4 DUP(?)
    ptr_a           db      0
menu_data ends    


code segment para USE16 'code'
assume cs:code, ds:menu_data, ss:stack
main:
    mov ax, menu_data
    mov ds, ax
    mov es, ax
    ; mov si, offset array
    ; mov dl, [si]
    ; mov cx, 8
    ; ; loop_2:
    ;     push [si]
    ;     add si, 2
    ;     loop loop_2
    mov ah, 01h
    mov cx, 4
    mov si, offset input_array
    inp:
        int 21h
        cmp al, 40h
        JA A_
        sub al, 30h
        jmp B_
    A_:
        sub al, 37h
    B_:
        mov [si], al
        inc si
        loop inp
    
    mov si, offset buff
    mov bx, offset input_array
    mov cl, 4
    read_byte:
        xor ax, ax
        xlatb
        mov dx, 8
    cycle_shift:
        and al, 11111111b ;;;;; TODODODODODODOOD!!!!!!!!!!!!!
        ; lahf
        shl al, 1
        mov byte ptr [si], '0'
        jnc last_zero
        mov byte ptr [si], '1'
    last_zero:
        inc si
        dec dx
        test dx, dx
        jnz cycle_shift
        inc bx
        dec cl
        test cl, cl
        JNZ  read_byte
   
   
   
    mov ah, 02h 
    
    ; mov cx, 32
    ; mov si, offset point
    ; dec si 
    ; dec si
    ; print_a:
    ;     mov dl, [si]
    ;     int 21h
    ;     dec si
    ;     loop print_a
    
    
    mov dl, 13
    int 21h
    mov dl, 10
    int 21h
    mov cx, 32
    mov si, offset buff
    print_b:
        mov dl, [si]
        int 21h
        inc si
        loop print_b    
    
    
    ; mov si, offset point
    ; dec si
    ; dec si
    ; print_point:
    ;     mov dl, point
    ;     int 21h
    ;     test cx, cx
    ;     JZ volver
    ;     mov bx, 4
    ; print_array:
    ;     mov dl, [si]
    ;     int 21h
    ;     dec si
    ;     dec bx
    ;     dec cx
    ;     test bx, bx
    ;     JZ  print_point
    ;     test cx, cx
    ;     JNZ print_array 
    volver:
    mov ax, 4C00h
    int 21h
code ends
end main
