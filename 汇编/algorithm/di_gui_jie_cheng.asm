section .data
	n: dd 5
section .text
global _start
_start:
	
	mov ebx,[n]
	xor edx,edx
	mov eax,1
	;设置当值为0时的初始值1
	cmp ebx,0
	je init_data
	call _calculate
	jmp init_data
_calculate:
	push ebx
_begin:
	cmp ebx,1
	je ret_main
	;不是1的时候
	dec ebx
	call _calculate
	
ret_main:
	pop ebx
	mul ebx
	ret
init_data:
	mov ebx,eax
	jmp ok
ok:
	mov eax,1
	int 0x80	
