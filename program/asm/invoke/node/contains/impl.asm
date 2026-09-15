global asm_list_find
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
asm_list_find:
    PUSH_REGISTERS
    ;取出头节点、target
    mov esi,[ebp+12]
    mov eax,[ebp+16]

begin_find:
    test esi,esi
    jz _no_find
    ;node.val
    mov ecx,[esi]
    cmp ecx,eax
    ;相同则找到了
    je _find_yes
    ;node.next
    mov edx,[esi+4]
    lea esi,[edx]
    jmp begin_find
_find_yes:
    mov eax,1
    jmp _ret
;没找到
_no_find:
    mov eax,0
_ret:
    _RET_FUNC