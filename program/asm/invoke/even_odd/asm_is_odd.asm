global asm_is_odd
section .text
asm_is_odd:
	push ebp
	mov ebp,esp
	mov eax,[ebp+8]
	and eax,0x1
	mov esp,ebp
	pop ebp
	ret
