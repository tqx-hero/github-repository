;删除链表节点
global asm_list_delete
section .text

%macro PUSH_REGISTERS 0
    push ebp
    push esi
    push ebx
    push edi
    mov ebp,esp
%endmacro
%macro _RET_FUNC 0
    mov esp,ebp
    pop edi
    pop ebx
    pop esi
    pop ebp
    ret
%endmacro

asm_list_delete:
    PUSH_REGISTERS
    sub esp,16
    ;取出链表头节点指针、目标数target
    mov edx,[ebp+20]
    mov eax,[ebp+24]
    ;设置sentinel节点
    mov dword [ebp-16],0xFFFFFFF0
    mov dword [ebp-12],edx
    ;设置节点prev初始为哨兵节点
    lea edi,[ebp-16]
    ;cur = sentinel.next
    lea esi,[edx]
delete_node:
    test esi,esi
    jz _ret
    mov ecx,[esi]
    cmp ecx,eax
    ;相同，删除节点，返回
    je _delete_cur
    ;tmp = node.next
    mov ebx,[esi+4]
    ;prev =node
    lea edi,[esi]
    ;node =node.next
    lea esi,[ebx]
    jmp delete_node
;删除当前节点
_delete_cur:
    ;获取cur.next
    mov eax,[esi+4]
    ;prev.next = cur.next
    mov [edi+4],eax
    mov dword [esi+4],0
    jmp _ret
_ret:
    mov eax,dword [ebp-12]
    _RET_FUNC
