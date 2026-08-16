section .data
  str: db 'Hello World!',0xA,0

section .text
global _start
_start:
	mov edi,0
lp:
	mov al,[str+edi]
	cmp al,0
	je exit_call
	mov eax,4
	mov ebx,1
	lea ecx,[str + edi]
	mov edx,1
	int 0x80
	inc edi
	jmp lp

exit_call:
	mov eax,1
	mov ebx,0
	int 0x80
