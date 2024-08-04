; .686
; .MODEL FLAT, C
; .STACK
.DATA 
    n REAL8 12.13232
.CODE
GetAssemblerTime PROC
    push rbp
    mov rbp, rsp
    mov rcx, [rbp + 24]
    mov rbx, [rbp + 16]
    finit 
    fld n
    fld st(0)
    L1: 
        fadd 
        loop L1
    pop rbp

    mov eax, 1
    xor ebx, ebx
    ret
GetAssemblerTime ENDP
END