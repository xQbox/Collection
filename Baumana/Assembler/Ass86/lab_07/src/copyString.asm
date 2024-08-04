; .686
; .MODEL FLAT, C
; .STACK
.CODE
copyString PROC
    push rbp
    mov rbp, rsp
    cld 
    mov rcx, [rbp + 32]
    mov rsi, [rbp + 24]
    mov rdi, [rbp + 16]
    rep movsb 
    pop rbp
    ret
copyString ENDP
END


; .CODE
; copyString PROC
;     push rbp
;     mov rbp, rsp
;     mov rcx, [rbp + 32]
;     mov rbx, [rbp + 24]
;     mov rsi, [rbp + 16] 
;     mov rax, rsi
;     L1:
;         mov dl, [rbx]
;         mov [rsi], dl
;         inc rbx
;         inc rsi
;         loop L1
;     pop rbp
;     ret
; copyString ENDP
; END