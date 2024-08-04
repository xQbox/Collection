stack segment para use16 stack 'stack'
	db 200h DUP (?)
stack ends
data segment dword 'data'
	input_message_1 db 13, 10, 'Text your frst numbers here: ', '$'
	input_message_2 db 13, 10, 'Text your scnd number here: ', '$'
data ends
code segment para use16 'code'
assume cs:code, ds:data
	 start:
	 mov ax, data
  	 mov ds, ax
   	 mov dx, offset input_message_1  
	 mov ah, 09h
	 int 21h
 	 mov ah, 01h
	 int 21h
	 mov ah, 02h
	 push ax
	 mov dl, 13
	 int 21h
	 mov dl, 10
	 int 21h
	 pop ax
	 mov dl, al
	 int 21h
	 mov dx, offset input_message_2  
	 mov ah, 09h
	 int 21h
 	 mov ah, 01h
	 int 21h	
  	 mov ah, 02h
	 push ax
  	 mov dl, 13
	 int 21h
	 mov dl, 10
	 int 21h
	 pop ax
	 mov dl, al
	 int 21h
	 mov dl, 13
	 int 21h
	 mov dl, 10
	 int 21h
	 mov ah, 01h
	 int 21h
 	 mov ah, 4Ch
	 int 21h
code ends
end start