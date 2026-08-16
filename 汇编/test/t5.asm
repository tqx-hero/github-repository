section .data
	arr: dd 1,2,3,4,5
	len equ ($ - arr) /4 
section .text
global _start
_start:
	lea esi,[arr]
	mov ecx,len
	xor ebx,ebx
lp:
	add ebx,[esi]
	add esi,4
	loop lp
	
	mov eax,1
	int 0x80
	
