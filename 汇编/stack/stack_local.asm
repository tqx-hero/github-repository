section .text
global _start
_start:
	call cal_sum
	mov eax,1
	int 0x80

cal_sum:
	push ebp
	push eax
	mov ebp,esp
	;开辟栈帧空间
	sub esp,8
	;为局部变量设置内存单元，赋值
	mov dword [ebp-4],12
	mov dword [ebp-8],27
	xor ebx,ebx
	;取值
	mov eax,[ebp-4]
	mov ebx,[ebp-8]
	add ebx,eax
	;销毁栈帧
	mov esp,ebp
	pop eax
	pop ebp
	ret

