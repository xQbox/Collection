
.386

extrn input_array_16:byte
; o_data segment para USE16 'data'
; extrn unsigned_2_array:byte

; o_data ends
public print_out_results
o_code segment para USE16 'code'
assume cs:o_code ;ds:o_data
print_out_results proc far USES ds

    mov ah, 02h
    mov cl, 0h
    mov bh, 4h
    jmp print_point
    print_result:
        mov dl, es:[si]
        int 21h
        inc si
        inc cl
        inc bh
        cmp bh, dh
        JE print_point
        jmp print_result
    print_point:
        mov dl, 2Eh
        int 21h
        my_loop:
            inc si
            dec bh
            test bh, bh
            jnz my_loop
        add cl, bl
        ; mov bh, 0h
        cmp cl, ch
        JAE exit_print
        jmp print_result
    
    exit_print:
        ret
print_out_results endp
o_code ends
end