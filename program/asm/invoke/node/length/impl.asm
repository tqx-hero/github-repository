global asm_list_length
%macro PUSH_REGISTERS 0
    push ebp
    push esi
    mov ebp,esp
%endmacro
%macro _RET_FUNC 0
    mov esp,ebp
    pop esi
    pop ebp
    ret
%endmacro
section .text
asm_list_length:
    PUSH_REGISTERS
    ;拿到链表头节点
    mov esi,[ebp+12]
    xor eax,eax
cal_len:
    test esi,esi
    ;指针=NULL
    jz _end_cal
    ;不为NULL，计数器+1
    inc eax
    mov ecx,[esi+4]
    lea esi,[ecx]
    jmp cal_len
_end_cal:
    _RET_FUNC
