global asm_array_max
extern print_max
section .text
asm_array_max:
	push ebp
	push esi
	mov ebp,esp
	
	mov esi,[ebp+12]
	mov ecx,[ebp+16]
	;保存当前最大值
	xor eax,eax
_find_max:
	dec ecx
	cmp ecx,0
	jl end_find
	mov edx,dword [esi+ecx*4]
	;找到这个数,与eax当前最大值比较
	cmp eax,edx
	;如果大于当前最大值，替换
	jl update_max

_continue_find:
	jmp _find_max

update_max:
	mov eax,edx
	jmp _continue_find

end_find:
	;将最大值eax压入栈内
	push eax
	call print_max
	pop eax
	mov esp,ebp
	pop esi
	pop ebp
	ret
