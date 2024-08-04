.8086
code SEGMENT para use16 PUBLIC 'code'
ASSUME CS:code, DS:data, SS:stack
	START:
		mov ax, data
		mov ds, ax  
		mov ah, 09h 
		mov dx, offset message
		int 21h
		mov ax, 4C00h
		int 21h
code ends
;
data SEGMENT PARA USE16 PUBLIC 'data'
	message db 'Hello, iamALEX$';
data ends
;
stack SEGMENT para use16 public 'stack'
	db 256 DUP(?)
stack ends
;
end START