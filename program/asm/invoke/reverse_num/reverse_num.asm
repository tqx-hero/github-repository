global asm_not
section .text
asm_not:
	push ebp
	mov ebp,esp
	;取出整数
	mov eax,[ebp+8]
	;xor eax,0xFFFFFFFF
	;可以直接用not
	not eax
	mov esp,ebp
	pop ebp
	ret
