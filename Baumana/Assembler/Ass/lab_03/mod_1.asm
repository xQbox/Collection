stack_mode_1 segment para stack 'stack'
    stack db 64 DUP ('STACK+++')
stack_mode_1 ends
; data_mode_1 segment para 'data'
;     first_number db ?
; data_mode_1 ends
    extrn first_number:BYTE
    extrn second_number:BYTE
    extrn output_message:WORD ; ЧТО НУЖНО УКАЗЫВАТ ПРИ РАБОТЕ С ПРЕДЛОЖЕНИЯМ (BYTE  WORD DWORD ???) 

code_mode_1 segment 'code'
assume cs:code_mode_1
public close
extrn start_point:far
    
main:       mov ax, code_mode_1
            mov bx, offset close
            push bx
            jmp start_point


close:      mov bx, ds
            mov al, byte ptr [bx + 1]           ; КАК ИЗБАВИТЬСЯ ОТ УСЛОВНОЙ АДЕРСАЦИИ И
            ;mov dl, byte ptr [bx]               ; ИСПОЛЬЗОВАТЬ МЕТКИ (НАЗВАНИЯ ПЕРЕМЕННЫХ)
            sub al, dl
            mov ah, 09h
            mov dx, offset output_message
            int 21h
            mov ah, 02h
            mov dl, al
            add dl, 30h
            int 21h
            mov ax, 4C00h
            int 21h   
code_mode_1 ends
end main