global asm_avg
section .text
asm_avg:
	push ebp
	push esi
	mov ebp,esp
	sub esp,4
	;数组首地址与数组的长度
	mov esi,[ebp+12]
	mov ecx,[ebp+16]
	mov [ebp-4],ecx
	xor ecx,ecx
	xor eax,eax
;数组元素相加
_add_arr:
	cmp ecx,[ebp-4]
	;偏移大于等于长度，退出
	jge end_add
	mov edx,ecx
	shl edx,2
	add eax,[esi+edx]
	inc ecx
	jmp _add_arr

end_add:
	xor edx,edx
	idiv dword [ebp-4]
	mov esp,ebp
	pop esi
	pop ebp
	ret
