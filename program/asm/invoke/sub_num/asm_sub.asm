global asm_sub
section .text
asm_sub:
	push ebp
	mov ebp,esp
	mov eax,[ebp+8]
	sub eax,[ebp+12]
	mov esp,ebp
	pop ebp
	ret
