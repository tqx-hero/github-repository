global asm_atoi
section .text
asm_atoi:
	push ebp
	push esi
	push edi
	push ebx
	mov ebp,esp
	;开辟8字节空间，用于存放字符串首地址与字符串长度
	sub esp,64
	;获取字符串的首地址
	mov esi,[ebp+20]
	;[ebp-4]=字符串首地址,[ebp-8]存放结果
	mov dword [ebp-4],esi
	mov dword [ebp-8],0
	xor ecx,ecx
	;设置存放转化后数字的起始地址
	lea edi,[ebp-9]
begin_push:
	;获取字符
	mov al,[esi+ecx]
	test al,al
	jz end_push
	;没到\0，就将al计算转化成数字
	sub al,'0'
	mov edx,ecx
	neg edx
	mov byte [edi+edx],al
	inc ecx
	jmp begin_push

end_push:
	;计算最大偏移量
	xor ebx,ebx
	xor eax,eax
	mov esi,10
begin_cal:
	cmp ebx,ecx
	jge end_cal
	;结果取出来，*10
	mov eax,dword [ebp-8]
	mul esi
	mov dword [ebp-8],eax
	mov edx,ebx
	neg edx
	mov dl,[edi+edx]
	movzx eax,dl
	add dword [ebp-8],eax
	inc ebx
	jmp begin_cal
;计算结束
end_cal:
	mov eax,dword [ebp-8]
	mov esp,ebp
	pop ebx
	pop edi
	pop esi
	pop ebp
	ret

