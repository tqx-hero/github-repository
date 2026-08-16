global asm_strcpy
section .text
asm_strcpy:
	push ebp
	push esi
	push edi
	mov ebp,esp
	;取出目标地址,与源地址
	mov edi,[ebp+16]
	mov esi,[ebp+20]
	xor ecx,ecx

str_cpy:
	mov al,[esi+ecx]
	mov [edi+ecx],al
	test al,al
	jz end_cpy
	inc ecx
	jmp str_cpy

end_cpy:
	mov esp,ebp
	pop edi
	pop esi
	pop ebp
	ret
