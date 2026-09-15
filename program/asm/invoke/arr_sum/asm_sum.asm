global asm_sum
section .text
asm_sum:
	push ebp
	push ebx
	push esi
	mov ebp,esp
	;取出长度len
	mov ebx,[ebp+20]
	;取出数组的首元素地址
	mov esi,[ebp+16]
	xor ecx,ecx
	xor eax,eax
_sum:
	cmp ecx,ebx
	jnl end_sum
	add eax,[esi+ecx*4]
	inc ecx
	jmp _sum

end_sum:
	mov esp,ebp
	pop esi
	pop ebx
	pop ebp
	ret

