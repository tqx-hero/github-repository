section .data
	n: dd 7
	buf: db 0
section .text
global _start
_start:
	mov ebx,[n]
	mov eax,1
	xor edx,edx
	xor ecx,ecx
lp:
	test ebx,ebx
	jz push_enter
	mul ebx
	dec ebx
	jmp lp
;将换行符压入栈内
push_enter:
	push 0xA
	inc ecx

;将结果拆分，按照由低到高压栈
push_stack:
	xor edx,edx
	mov ebx,0xA
	;除以10，取余数，即取最低位
	div ebx
	;将余数，即结果的最低位压入栈内
	push edx
	inc ecx
	;查看商是不是为0，不为0循环该方法
	test eax,eax
	jnz push_stack

print_result:
	pop eax
	dec ecx
	;计算ASCII
	test ecx,ecx
	jz print_enter
	add al,'0'
	call print_func
	jmp print_result

print_enter:
	call print_func
	jmp ok
;打印函数
print_func:
	push eax
	push ebx
	push ecx
	push edx

	;将ASCII放入缓冲区buf
	mov [buf],al
	;调用sys_write打印
	mov eax,4
	mov ebx,1
	mov ecx,buf
	mov edx,1
	int 0x80

	pop edx
	pop ecx
	pop ebx
	pop eax

	ret

ok:

	;退出

	mov ebx,0
	mov eax,1
	int 0x80
