global asm_sum_struct
section .text
asm_sum_struct:
	push ebp
	push esi
	mov ebp,esp
	;结构体指针
	mov esi,[ebp+12]
	mov eax,[esi]
	add eax,[esi+4]
	mov esp,ebp
	pop esi
	pop ebp
	ret
