global asm_strrev
section .text
extern strlen
asm_strrev:
	push ebp
	push esi
	push ebx
	mov ebp,esp
	sub esp,16
	;取出字符串首地址
	mov esi,[ebp+16]
	;计算字符串的长度
	push esi
	call strlen
	add esp,4
	;获取字符串的末尾偏移
	dec eax
	;将字符串的left、right指针放入栈内局部变量
	mov dword [ebp-16],0
	mov dword [ebp-12],eax

_str_rev:
	mov eax,dword [ebp-16]
	mov ebx,dword [ebp-12]
	;left >=right,结束循环
	cmp eax,ebx
	jge _end_rev
	;交换两内存单元内的数据
	mov dl,[esi+eax]
	mov cl,[esi+ebx]
	mov byte [esi+eax],cl
	mov byte [esi+ebx],dl
	;left++,right--
	inc dword[ebp-16]
	dec dword [ebp-12]
	jmp _str_rev

_end_rev:
	mov esp,ebp
	pop ebx
	pop esi
	pop ebp
	ret
