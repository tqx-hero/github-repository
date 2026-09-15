section .data
	arr: dd 12,45,7,89,23,56
	len equ ($ - arr)/4
section .text
global _start
_start:
	lea esi,[arr+4]
	mov ebx,[arr]
	mov ecx,len-1
lp:
	;比较大小，比当前最大值大，则替换
	cmp [esi],ebx
	jg  replace_data
lp1:
	add esi,4
	loop lp
	jmp ok	

replace_data:
	mov ebx,[esi]
	jmp lp1

ok:
	mov eax,1
	int 0x80
