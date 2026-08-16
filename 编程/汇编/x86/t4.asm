section .data
num: dd 10
section .text
global _start
_start:
	mov eax,10
	mov ebx,65
	lock cmpxchg [num],ebx
	je success
	mov [num],eax
	jmp ok
success:
	mov eax,4
	mov ebx,1
	lea ecx,[num]
	mov edx,1
	int 0x80

ok:
	mov eax,1
	mov ebx,0
	int 0x80
