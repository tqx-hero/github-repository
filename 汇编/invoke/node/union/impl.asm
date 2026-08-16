;拼接2个有序链表
global asm_list_merge
section .text
%macro PUSH_REGISTERS 0
	push ebp
	push ebx
	push esi
	push edi
	mov ebp,esp
%endmacro

%macro _RET_FUNC 0
	mov esp,ebp
	pop edi
	pop esi
	pop ebx
	pop ebp
	ret
%endmacro

%macro TEST_JZ 2
    test %1,%1
    jz %2
%endmacro
%macro TEST_JNZ 2
    test %1,%1
    jnz %2
%endmacro

%macro TO_NEXT_NODE 1
    mov eax,[%1+4]
    lea %1,[eax]
%endmacro

%macro GET_PARAM2 2
    mov %1,[ebp+20]
    mov %2,[ebp+24]
%endmacro

asm_list_merge:
    PUSH_REGISTERS
    sub esp,64
    ;2个node根节点l1,l2
    GET_PARAM2  ESI,EDI
    ;新建sentinel哨兵节点:[ebp-64]
    ;哨兵节点next=null
    mov dword [ebp-60],0
    ;cur节点
    lea edx,[ebp-64]

union_node:
    TEST_JZ esi,_end_loop
    TEST_JZ edi,_end_loop
    ;v1与v2
    mov eax,[esi]
    mov ebx,[edi]
    cmp eax,ebx
    ;v1<=v2,拼接l1
    jle union_h1
    ;v1>v2,拼接l2
    ;cur.next = l2
    mov dword [edx+4],edi
    ;l2=l2.next
    TO_NEXT_NODE edi
_inc_cur:
    TO_NEXT_NODE edx
    jmp union_node
;拼接h1
union_h1:
    ;cur.next = l1
    mov dword [edx+4],esi
    ;l1=l1.next
    TO_NEXT_NODE esi
    jmp _inc_cur
;跳出循环，链接剩余的节点
_end_loop:
    ;l1还有剩余的，拼接上
    TEST_JNZ esi,union_left_h1
    ;l2为0，直接返回
    TEST_JZ edi,_ret
    ;l2不为0，拼接l2
    mov dword [edx+4],edi
    jmp _ret
union_left_h1:
    mov dword [edx+4],esi
_ret:
    ;返回指针=sentinel.next
    mov eax,dword [ebp-60]
    _RET_FUNC