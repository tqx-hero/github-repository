global asm_strcat

section .text
asm_strcat:
	push ebp
	push esi
	push edi
	mov ebp,esp
	;拿到源地址与目标地址
	mov edi,[ebp+16]
	mov esi,[ebp+20]
;找到目标地址的末尾\0
find_last:
	mov al,[edi]
	test al,al
	jz begin_cat
	inc edi
	jmp find_last

;开始追加字符
begin_cat:
	mov al,[esi]
	mov byte [edi],al
	test al,al
	;拷贝字符如果是ASCII=0，则结束
	jz end_cpy
	inc esi
	inc edi
	jmp begin_cat

end_cpy:
	mov esp,ebp
	pop edi
	pop esi
	pop ebp
	ret
