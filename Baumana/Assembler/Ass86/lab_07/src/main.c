#include <stdio.h>
#include <string.h>


void copyString();

int main(void)
{
    char szString[100];
    // char tmp[2];
    printf("Write string below\n>> ");
    if (!(fgets(szString, 100, stdin)))  return -1;  
    // scanf("%*[^\n]");
    printf("%s\n", szString);
    szString[strlen(szString) - 1] = '\0';
    char *pStart = &szString[0];
    long long int s;
    __asm{
        jmp start           ;
    EmulateProc:            ;
        push rbp            ;
        mov rbp, rsp        ;
        mov rdi, [rbp + 16]        ;
        xor rcx, rcx
        dec rcx
        xor rax, rax
        mov al, 0
        cld
        repne scasb
        not rcx 
        mov rax, rcx
        pop rbp             ;
        ret                 ;
    start:
        push rax            ;
        push rdi            ;
        push rcx
        push pStart         ;

        call EmulateProc    ;
        add rsp, 8          ;
        mov s, rax              ;
        pop rcx
        pop rdi             ;
        pop rax             ;
    }
    printf("strlen >> %lld\n", s);
    
    printf("Write first string below\n>>");
    if (!(fgets(szString, 100, stdin)))  return -1; 

    szString[strlen(szString) - 1] = '\0';
    pStart = &szString[0];
    long long int liSize = strlen(szString);
    char szSecondString[100] = {0};
    char *pSecondStart = &szSecondString[0];
    __asm{
        push rax
        push rbx
        push rdx
        push rcx
        push rsi
        push liSize
        push pStart
        push pSecondStart
    }
    copyString();
    __asm{
        add rsp, 24
        mov pSecondStart, rax
        pop rsi
        pop rcx
        pop rdx
        pop rbx
        pop rax
    }

    for (long int i = 0; i < liSize; ++i)
    {
        printf("%c\n", *(pSecondStart + i));     
    }
    
    return 0;
}



    // __asm{
    //     jmp start

    // Emulate:
    //     push ebp
    //     mov ebp, esp
    //     mov ecx, [ebp + 16]
    //     mov ebx, [ebp + 12]
    //     mov esi, [ebp + 8] 
    //     mov eax, esi
    //     L1:
    //         mov dl, [ebx]
    //         mov [esi], dl
    //         inc ebx
    //         inc esi
    //         loop L1
    //     pop ebp
    //     ret
        


    // start:
    //     push eax
    //     push ebx
    //     push edx
    //     push ecx
    //     push esi
    //     push liSize
    //     push pStart
    //     push pSecondStart
        
    //     call Emulate
    //     add esp, 12
    //     mov pSecondStart, eax
    //     pop esi
    //     pop ecx
    //     pop edx
    //     pop ebx
    //     pop eax
    // }


    
    // __asm{
    //     jmp start           ;
    // EmulateProc:            ;
    //     push rbp            ;
    //     mov rbp, rsp        ;
    //     mov rbx, [rbp + 16]        ;
    //     xor rax, rax
    //  L1:                    ;
    //     mov dl, [rbx]       ;
    //     inc rax             ;
    //     inc rbx             ;
    //     cmp dl, 0           ;
    //     JNE L1              ;

    //     pop rbp             ;
    //     ret                 ;
    // start:
    //     push rax            ;
    //     push rbx            ;
    //     push rdx            ;
    //     push pStart       ;

    //     call EmulateProc    ;
    //     add rsp, 8          ;
    //     dec rax             ;
    //     mov s, rax              ;
    //     pop rdx             ;
    //     pop rbx             ;
    //     pop rax             ;
    // }