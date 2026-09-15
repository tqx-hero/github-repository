section .data
section .text
global _start
_start:
	mov eax,50
	mov ebx,8
	mov edx,0
	mul ebx
	mov ebx,5
	div ebx
	mov ecx,eax
	mov eax,1
	mov ebx,ecx
	int 0x80
