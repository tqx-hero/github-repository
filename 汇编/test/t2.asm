section .text
global _start
_start:
	mov eax,28
	;mov ecx,eax
	mov ebx,14
	mov ecx,ebx
	add ebx,eax
	sub eax,ecx
	mov ecx,eax
	;调用系统退出
	mov eax,1
	mov ebx,0
	int 0x80
