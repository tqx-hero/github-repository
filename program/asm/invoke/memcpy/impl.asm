global asm_memcpy
section .text
asm_memcpy:
	push ebp
	push esi
	push edi
	mov ebp,esp
	;dst
	mov edi,[ebp+16]
	;src
	mov esi,[ebp+20]
	;len
	mov ecx,[ebp+24]
	xor edx,edx
	
_mem_cpy:
	;大于等于，结束拷贝
	cmp edx,ecx
	jge _end_cpy
	mov al, byte [esi+edx]
	mov byte [edi+edx],al
	test al,al
	;如果字符为\0，拷贝结束
	jz _end_cpy
	inc edx
	jmp _mem_cpy
_end_cpy:
	
	mov esp,ebp
	pop edi
	pop esi
	pop ebp
	ret