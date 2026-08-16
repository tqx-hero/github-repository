section .data
	n: dd 4
section .text
global _start
_start:
	mov ebx,[n]
	;初始化斐波那契数:edx=f(0)=0,ecx=f(1)=1
	
	call _calculate
	
	jmp ok

init_data:
	add eax,ecx
	jmp ok

_calculate:
	push ebx
	
	;出口1，当ebx=0时
	cmp ebx,0
	je ret_zero
	;出口2，ebx=1时
	cmp ebx,1
	je ret_one
	;都不满足，则进行计算
	;计算-1的
		
	
	
	dec ebx
	call _calculate
	
	push eax

	;计算-2的数
	dec ebx
	
	call _calculate
	;计算eax和，并更新edx=ecx，ecx=eax
	pop ecx
	add eax,ecx
	;mov edx,ecx
	;mov ecx,eax	
	jmp ret_cal
ret_one:
	mov eax,1
	
	jmp ret_cal
ret_zero:
	mov eax,0
	jmp ret_cal

ret_cal:
	pop ebx
	ret

ok:
	mov ebx,eax
	mov eax,1
	int 0x80
	
