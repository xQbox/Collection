stack segment para stack 'stack'
    stack_space db 100h DUP ('STACK+++')
stack ends

data segment word public 'data'
    matrix db 9 dup(9 dup (35h, 31h, 39h))
    ; matrix_row_size db 39h                    ; Максимальный размер строк в матрице
    col db 1
    row db 1
    step db 1                                 ; Размер шага для пропуска фиктивных адресов ( matrix_col_size - col )
data ends


HelloMsg segment para public 'data'
    col_msg db 13, 10,'Input columns: ', 13, 10, '$'
    row_msg db 13, 10,'Input rows: ', 13, 10, '$'
    entrance_msg db 13, 10, 'Input matrix: ', 13, 10, '$'
    new_row db 13, 10, '$'
    output_message db 13, 10,"Result: ", 13, 10, '$'
    empty_array_message db 13, 10, "Empty", 13, 10, '$'
HelloMsg ends

    
 
code segment para public 'code'
; Процедура ввода матрицы размера матрицы  
input_matrix_size proc near
        row_in:
            mov ah, 09h
            mov dx, offset row_msg
            int 21h
            mov ah, 01h
            int 21h
            cmp al, 39h
            jnb row_in 
            cmp al, 31h
            jna row_in
        mov es:row, al
        col_in:
            mov ah, 09h
            mov dx, offset col_msg
            int 21h
            mov ah, 01h
            int 21h
            cmp al, 39h
            jnb col_in 
            cmp al, 31h
            jna col_in
        mov es:col, al
        ret
input_matrix_size endp

; Процедура печати новой строки для матрицы 
new_line proc near
                mov ah, 09h 
                mov dx, offset new_row
                int 21h
                ret
new_line endp
; конец процедуры

; процедура чтения матрица - проход по строчкам
print_matrix proc near
                mov al, es:col
                cmp al, 30h
                JE  return4
                mov ah, 09h
                mov dx, offset output_message
                int 21h
                mov al, 39h                 ; макисмальный размер строки
                sub al, es:col              
                mov es:step, al             ; размер шага для пропуска фиктивных адресов 
                mov ah, 02h
                mov bx, 0h 
                mov cl, 30h                  
                input_rows:
                    cmp cl, es:row
                    JAE return3               ; условие выхода из внешнего цикла  
                    mov ch, 30h
                    inc cl
                    input_cols:
                        mov dl, es:[matrix + bx]
                        int 21h
                        inc bl              ; Шаг по матрице ( массиву )
                        inc ch              ; Шаг для проверки условия ( bl <= col (30h - старт))
                        cmp ch, es:col
                        jnae input_cols
                        add  bl, es:step    
                        call new_line
                        mov ah, 02h
                        jmp input_rows
                return3:
                ret
                return4:
                mov ah, 09h
                mov dx, offset empty_array_message
                int 21h
                ret

print_matrix endp 

; Конец процедуры

input_matrix_data proc near
                
                mov ah, 09h
                mov dx, offset entrance_msg
                int 21h
                mov al, 39h
                sub al, es:col           
                mov es:step, al                 ; Размер шага для пропуска фиктивных адресов 
                mov ah, 01h
                mov bx, 0h 
                mov cl, 30h                     ; Установка регистра в 'цифровой' 0 для работы с матрицей ( cl - строки )
                rows:
                    cmp cl, es:row              ; Условие выхода из внешнего цикла
                    jae return1                 ;   
                    mov ch, 30h                 ; Установка регистра в 'цифровой' 0 для работы с матрицей ( ch - столбцы )
                    inc cl                      ; Увеличения значения строк
                    cols:
                        int 21h
                        cmp al, 39h
                        jna cols
                        mov es:[matrix + bx], al 
                        inc bl                  ; Переход к следующему элементу матрицы по стобцу
                        inc ch                  ; Увеличения значения  колонок
                        cmp ch, es:col          ; Условие  выхода из цикла
                        jnae cols               ; 
                        add  bl, es:step        ; Переход к следующему элементу матрицы по стобцу     
                        call new_line           ; Вызов процедуры переноса строки ~'\n'
                        mov ah, 01h         
                        jmp rows                ; Прыжок на метку (переход в начало цикла)
                return1:
                ret
input_matrix_data endp
             
; Процедура лабораторной работы ( удалить все столбцы содержащие только А )
; Реализовано с помощью алгоритма циклического сдвига вправо + уменьшение значения столбцов
task proc near
        mov bx, offset matrix                   ; Установка регистра bx в логический адреса начала матрицы
        mov ch, 30h                             ; Установка регистра в начальную позицию для подсчета строк
        mov cl, 30h                             ; Установка регистра в начальную позицию для подсчета столбцов
        new_col: 
            push bx
        start:
            cmp es:[matrix + bx], 41h           ; Проверка на А
            JNE next_col
            inc ch
            cmp ch, es:row
            JE delete
            add bx, 09h                         ; Переход на следующую строчку матрицы
            jmp start
        next_col:
            pop bx
            inc bx
            inc cl
            cmp cl, es:row
            JE exit
            jmp new_col
        delete:
            push cx 
            push bx
            shift:                              ; Алгоритм сдвига влево на одни символ
                mov al, es:[matrix + bx + 1]    
                mov es:[matrix + bx], al 
                inc bl
                inc cl
                cmp cl, es:col
                JNE shift       
            pop bx
            pop cx
            dec ch
            sub bx, 09h                         
            cmp ch, 30h
            JNE delete
            add bx, 09h
            dec es:col
            jmp start
        exit:
            ret    


task endp

main:   
assume cs:code, ds:HelloMsg, ss:stack 
        
        mov ax, HelloMsg
        mov ds, ax
        mov ax, data
        mov es, ax
        call input_matrix_size              
        call input_matrix_data
        call task
        call print_matrix
        mov ax, 4C00h
        int 21h 
code ends
end main

