global asm_mul
extern printf
section .data
	fmt: db "mul = %d",0xA,0	
section .text
asm_mul:
	push ebp
	mov ebp, esp
	push ebx
	xor edx,edx
	mov eax,[ebp+8]
	mov ebx,[ebp+12]
	mul ebx
	
	pop ebx

	push eax
	push fmt
	call printf
	add esp,4
	pop eax
	mov esp,ebp
	pop ebp
	ret
