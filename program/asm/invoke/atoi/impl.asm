
BEGIN equ 0xA
ZERO EQU '0'
NINE equ '9'
global asm_atoi
section .text
%macro  PUSH_REGISTERS 0
    push ebp
    push esi
    push edi
    push ebx
    mov ebp,esp
%endmacro
%macro RET_FUNC 0
    mov esp,ebp
    pop ebx
    pop edi
    pop esi
    pop ebp
    ret
%endmacro
asm_atoi:
    PUSH_REGISTERS
    ;拿到字符串首字符地址
    mov esi,[ebp+20]
    mov ebx,BEGIN
    xor eax,eax

loop_get:
    mov  cl,[esi]
    cmp cl,ZERO
    jl _end
    cmp cl,NINE
    jg _end
    sub cl,ZERO
    mul ebx
    movzx edx,cl
    add eax,edx
    inc esi
    jmp loop_get
_end:
    RET_FUNC


