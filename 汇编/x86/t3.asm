section .data
    str db "Hello World!",0xA
    len equ $ - str
    
section .text
global main
main:
    ;write your code here
    mov eax,4
    mov ebx,1
    mov ecx,str
    mov edx,len
    int 0x80
    
    mov eax,1
    mov ebx,0
    int 0x80