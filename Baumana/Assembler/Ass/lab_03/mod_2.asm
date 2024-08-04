stack_mode_2 segment para stack 'stack'
    stack db 64 DUP ("STACK+++")
stack_mode_2 ends
data_mode_2 segment para public 'data'
    public second_number                                ; ВОПРОС В ПЕРВОМ МОДУЛЕ ????
        second_number db 1 DUP (?)
;    
    public first_number                                 
        first_number db 1 DUP (?)                       ; ВОПРОС В ПЕРВОМ МОДУЛЕ ????
;
    input_message db 13, 10, 'Input your numbers below: ', 13, 10, '$'
;    
    public output_message 
        output_message db 13, 10, 'Result is: ', '$'
data_mode_2 ends 

code_mode_2 segment para public 'code'
assume cs:code_mode_2, ds:data_mode_2 
    
public start_point

extrn close:far
start_point:    mov ax, data_mode_2
                mov ds, ax
                wrong_input: 
                mov cx, 2
                mov bx, data_mode_2
                label1:
                mov si, cx
                mov ah, 09h
                mov dx, offset input_message
                int 21h
                mov ah, 01h 
                int 21h
                mov byte ptr [bx + si - 1] , al                     ; КАК ЗДЕСЬ ИЗБАВИТЬСЯ ОТ РЕГИСТРОВ И РАБОТАТЬ С МЕТКАМИ
                loop label1 
                mov ah, byte ptr [bx + 1]
                mov al, byte ptr [bx]
                cmp ah, al
                JNA wrong_input
                mov ah, 09h
                mov dx, offset output_message
                int 21h
                mov ah, 02h
                mov dl, byte ptr [bx + 1]
                int 21h
                mov dl, byte ptr [bx]
                int 21h
                pop bx
                jmp bx
code_mode_2 ends
end