section .data
	buf: db 1024 dup (0)
section .text
global _start
_start:
	;将局部变量入栈，调用子函数计算平方和
	push 12
	push 15
	call _sum_square
	push eax
	;打印结果输出到屏幕
	call _print_number
	add esp,12
	;return 0
	mov eax,1
	mov ebx,0
	int 0x80
;计算平方和
_sum_square:
	push ebp
	mov ebp,esp
	;栈帧开辟12字节空间
	sub esp,8
	;取出主函数压入栈的数据放到这个栈中
	mov eax,[ebp+12]
	xor edx,edx
	mul eax
	mov dword [ebp-4],eax
	
	mov eax,[ebp+8]
	xor edx,edx
	mul eax
	mov dword [ebp-8],eax
	add eax,[ebp-4]

	;恢复栈指针
	mov esp,ebp
	pop ebp
	ret
;打印结果输出到屏幕
_print_number:
	push ebp
	mov ebp,esp
	sub esp,16
	;取出数据，结果放到eax
	mov eax,[ebp+8]
	mov ebx,0xA
	;先把换行放到栈内
	mov byte [ebp-1],bl
	mov esi,-2
cal_nums:
	xor edx,edx
	;计算eax的末尾，并将其压入栈内
	div ebx
	;将edx的结果转换成ASCII，之后把字符压入栈内
	add dl,'0'
	mov byte [ebp+esi],dl
	dec esi
	;当eax不为0时，继续循环压栈
	test eax,eax
	jnz cal_nums
	;当eax为0时，压栈结束，开始放入缓冲区
	lea edi,[buf]
	xor edx,edx
_in_buffer:
	inc esi
	test esi,esi
	;当esi为0，表明栈内数据已全部放到buf，这时开始打印
	jz _print_func
	;esi不为0，将相应偏移内存中的数据取出，放到buf
	mov al,[ebp+esi]
	mov [edi],al
	inc edi
	inc edx
	jmp _in_buffer
;缓冲区数据存放完毕，开始打印
_print_func:
	mov eax,4
	mov ebx,1
	mov ecx,buf
	int 0x80

	mov esp,ebp
	pop ebp
	ret
