global asm_strlen
section .text
asm_strlen:
	push ebp
	push esi
	mov ebp,esp
	;拿到字符串的首地址
	mov esi,[ebp+12]
	xor eax,eax
str_len_func:
	mov cl,byte [esi+eax]
	test cl,cl
	jz end_count
	inc eax
	jmp str_len_func
end_count:
	mov esp,ebp
	pop esi
	pop ebp
	ret
