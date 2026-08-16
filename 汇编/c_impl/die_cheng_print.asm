section .data
	buf: db 1024 dup (0)
section .text
global _start
_start:
	push 5
	xor edx,edx
	call _factorial_func
	;返回结果压栈
	push eax
	call _print_num
	mov eax,1
	mov ebx,0
	int 0x80
;打印数字
_print_num:
	push ebp
	mov ebp,esp
	sub esp,16
	;将结果拿去出来
	mov eax,[ebp+8]
	mov ebx,0xA
	mov edi,-1
	;先将换行符压入栈内
	mov byte [ebp+edi],0xA

;将字符结果压栈
_push_res:
	dec edi
	xor edx,edx
	;计算除法，取余数,转成ASCII
	div ebx
	add dl,'0'
	mov byte [ebp+edi],dl
	test eax,eax
	jnz _push_res
	
	xor edx,edx
	lea esi,[buf]
;填充缓冲区
_full_:
	test edi,edi
	;为0时，缓冲区填充结束，开始打印
	jz _begin_print
	;不为0时，取值，填充缓冲区
	mov al,[ebp+edi]
	mov [esi],al
	inc edi
	inc edx
	inc esi
	jmp _full_

_end_print:
	mov esp,ebp
	pop ebp
	ret
;开始打印结果
_begin_print:
	mov eax,4
	mov ebx,1
	mov ecx,buf
	int 0x80
	jmp _end_print

_factorial_func:
	push ebp
	mov ebp,esp
	sub esp,4
	;取出数据，将其放入栈内
	mov eax,[ebp+8]
	mov dword [ebp-4],eax
	cmp eax,1
	;小于等于1时退出当前循环
	jle ret_result
	;大于1时，继续递归执行函数
	dec eax
	push eax
	call _factorial_func
	jmp ret_current_func

ret_result:
	mov eax,1
	mov dword [ebp-4],1
ret_current_func:
	mul dword [ebp-4]
	mov esp,ebp
	pop ebp
	ret
