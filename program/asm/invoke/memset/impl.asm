global asm_memset
section .text
asm_memset:
	push ebp
	push edi
	push ebx
	mov ebp,esp
	sub esp,16
	;字符串指针
	mov edi,[ebp+16]
	;要填充的字符,需要取al
	mov eax,[ebp+20]
	;填充的长度
	mov ecx,[ebp+24]
	xor edx,edx
	
mem_change:
	cmp edx,ecx
	jge _end_change
	
	;判断当前字符是否为\0
	mov bl,byte [edi]
	test bl,bl
	jz _end_change

	mov byte [edi],al
	inc edi
	inc edx
	jmp mem_change
_end_change:
	mov esp,ebp
	pop ebx
	pop edi
	pop ebp
	ret
