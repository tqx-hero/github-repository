global asm_double
section .text
asm_double:
	push ebp
	mov ebp,esp
	mov eax,[ebp+8]
	shl dword [eax],1
	mov esp,ebp
	pop ebp
	ret
