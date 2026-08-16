section .text
global _start
_start:
	;mov ebp,esp
	push 5
	push 7
	call calc_func
	;主函数没必要再修复esp指针
	;程序退出后栈交还给操作系统
	;mov esp,ebp
	mov eax,1
	int 0x80

calc_func:
	push ebp
	mov ebp,esp
	sub esp,8
	
	push [ebp+8]
	call square_func
	mov dword [ebp-4],eax

	push [ebp+12]
	call square_func
	mov dword [ebp-8],eax
	;将结果取出来进行加法运算
	mov ebx,[ebp-8]
	add ebx,[ebp-4]
	mov esp,ebp
	pop ebp
	ret
;计算平方函数
square_func:
	push ebp
	mov ebp,esp
	sub esp,4
	mov eax,[ebp+8]
	xor edx,edx
	mul eax
	mov dword [ebp-4],eax
	mov esp,ebp
	pop ebp
	ret

