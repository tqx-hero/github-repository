global asm_fact
section .text
asm_fact:
	push ebp
	mov ebp,esp
	mov eax,[ebp+8]
	cmp eax,1
	jle _pop_res
	dec eax
	push eax
	call asm_fact
	add esp,4
	mul dword [ebp+8]
_ret_func:
	mov esp,ebp
	pop ebp
	ret

_pop_res:
	mov eax,1
	jmp _ret_func



