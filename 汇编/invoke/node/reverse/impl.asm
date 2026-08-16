;翻转链表
global asm_reverse_list
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
section .text
asm_reverse_list:
	PUSH_REGISTERS
	sub esp,64
	;链表头节点
	mov esi,[ebp+20]
	;prev :NULL
	mov edi,0
	
reverse_node:
	;cur指针
	test esi,esi
	;cur =0,翻转结束，返回edi
	jz _end_reverse
	;拿到 temp cur.next=[esi+4]
	mov eax,[esi+4]
	;cur.next=prev
	mov [esi+4],edi
	;prev =cur
	lea edi,[esi]
	;cur = temp
	lea esi,[eax]
	jmp reverse_node
_end_reverse:
	lea eax,[edi]
	_RET_FUNC
	