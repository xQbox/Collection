.386
.model huge
;Основное соглашения - вызывающая сторона следит за состояниями регистров
continueMsg EQU <"Would you like to continue (Y/N) ?">
SomSomichMsg EQU <"Are you sure? (Y/Y) ?">
; добавить макроопределению public 

extrn input_unsigned_16:far
extrn unsigned_2:far
extrn signed_8:far
extrn degree_of_two:far 

extrn print_out_results:far
extrn input_array_16:byte

stack segment para USE16 stack 'stack'
    stack_data      db      100h DUP('STACK+++') 
stack ends

public arr_start
menu_data segment USE16 'data'
    arr_start label far  
    demo_array      db      4 DUP(0Fh) ;0Ah, 0Bh, 0Ch, 0Dh              ; разобраться со смещением 
    new_line        db      13, 10, '$'
    input_line      db      13, 10, '>> ', '$'
    menu_text       db      13, 10, 'Select menu item: ',
                            13, 10, '1 - input unsigned 16', 13, 10, '2 - unsigned 2', 
                            13, 10, '3 - signed 8', 13, 10, '4 - degree of two', 13, 10, '0 - exit', '$'
    menu_array      dd      exit, input_unsigned_16, unsigned_2, signed_8, degree_of_two
    menu_array_size =       ($ - menu_array)
    menu_error_msg  db      13, 10, 'Incorrect menu item, try again.', '$'
    more            db      13, 10, continueMsg, 13, 10,'>> ', '$'
menu_data ends    


code segment para USE16 'code'
  
main:
        mov ax, menu_data
        mov ds, ax
        mov es, ax
        jmp menu
; Print Menu error (when users keystroke wrogn key)
    menu_error:
        mov dx, offset menu_error_msg
        mov ah, 09h
        int 21h

; Main Menu print 
    menu:
        mov dx, offset menu_text
        mov ah, 09h
        int 21h 
        mov dx, offset input_line
        int 21h
        mov ah, 01h
        int 21h
        cmp al, 34h
        JA  menu_error
        cmp al, 30h
        JB  menu_error 
    
    xor ah, ah
    sub ax, 30h
    mov cx, ax
    mov bx, offset menu_array

; BX preserve address of calling funcion    
    array_shift:
        add bx, 4
        loop array_shift
    call far ptr [bx]

; USER FRIENDLY INTERFACE
    ; mov ah, 09h
    ; mov dx, offset more
    ; int 21h
    ; mov ah, 01h
    ; int 21h
    ; cmp al, 59h
    ; JE  menu  
; USER FRIENDLY INTERFACE

; Cycle for Menu Print
    jmp menu
exit proc near
    mov ax, 4C00h
    int 21h
exit endp
code ends
end main
