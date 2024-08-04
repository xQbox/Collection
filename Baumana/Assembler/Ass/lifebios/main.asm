; .model small
.186
stack segment para stack 'stack' 
    stack_seg db 100h DUP('STACK+++')
stack ends
data segment para public 'data'
    db          320*200+1 dup(?)
data ends
code segment para public 'code'
start:
        mov ax, data
        mov ds, ax
        xor ax, ax
        int 1Ah
        mov di, 320 * 320 + 1
fill_buffer:
        imul dx, 4E35h
        inc dx
        mov ax, dx
        shr ax, 15
        mov byte ptr [di], al
        dec di
        jnz fill_buffer
        mov ax, 0013h
        int 10h
new_cycle:
        mov di, 320 * 320+1
step_1:
        mov al, byte ptr [di + 1]
        add al, byte ptr [di - 1]
        add al, byte ptr [di + 319]
        add al, byte ptr [di - 319] 
        add al, byte ptr [di + 320]
        add al, byte ptr [di - 320] 
        add al, byte ptr [di + 321]
        add al, byte ptr [di - 321]
        shl al, 4

        or byte ptr [di], al
        dec di
        jnz step_1
flip_cycle:
        mov al, byte ptr [di]
        shr al, 4
        cmp al, 3
        je birth
        cmp al, 2
        je f_c_continue
        mov byte ptr [di], 0
        jmp short f_c_continue
birth:
        mov byte ptr [di], 0
f_c_continue:
        and byte ptr [di], 0Fh
        dec di
        jnz flip_cycle
        mov si, 320*200+1
        mov cx, 319
        mov dx, 199
zdisplay:
        mov al, byte ptr [si]
        mov ah, 0Ch
        int 10h
        dec si
        dec cx 
        jns zdisplay
        mov cx, 319
        dec dx
        jns zdisplay
        mov ah, 1
        int 16h
        jz new_cycle
        mov ax, 0003h
        int 10h
        mov ax, 4C00h
        int 21h
code ends
end start