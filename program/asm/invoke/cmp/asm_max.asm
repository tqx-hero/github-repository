extern print_max
global asm_max
section .text

asm_max:
	push ebp
	mov ebp,esp
	mov eax,[ebp+8]
	mov ecx,[ebp+12]
	cmp eax,ecx
	jl change_num
_end:
	push eax
	call print_max
	pop eax
	mov esp,ebp
	pop ebp
	ret


change_num:
	xchg eax,ecx
	jmp _end
