NULL equ 0

%macro PUSH_REGISTERS 0
	push ebp
	mov ebp,esp
%endmacro
%macro _RET_FUNC 0
	mov esp,ebp
	pop ebp
	ret
%endmacro

global asm_reverse_recursive
section .text
asm_reverse_recursive:
    PUSH_REGISTERS
    ;取出链表头节点
    mov esi,[ebp+8]
    lea edi,[NULL]
    push edi
    push esi
    jmp call_func
next_str:
    add esp,8
    mov eax,edi
    _RET_FUNC

_end_func:
    add esp,8
    _RET_FUNC

begin_reverse:
    PUSH_REGISTERS
    mov esi,[ebp+8]
    mov edi,[ebp+12]
    cmp esi,NULL
    je _end_func
    mov eax,dword [esi+4]
    mov dword [esi+4],edi
    mov edi,esi
    mov esi,eax
    jmp ctn

call_func:
    push next_str
    jmp begin_reverse

ctn:
    push edi
    push esi
    call begin_reverse
    jmp _end_func
