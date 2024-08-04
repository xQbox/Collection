.8086
.model tiny
.code  
	ORG 100h;
        START:
        mov AH, 09h;
        mov DX, offset message;
        int  21h;
        int 20h;
        message db 'Hello, IamAlex!$';   
	NOP;
	NOP;
end START
