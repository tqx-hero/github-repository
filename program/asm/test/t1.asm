section .data
   str: db "Hello World",0xA
section .text
global _start
_start:
	mov edi,0
lp:
	mov al,[str+edi]
	cmp al,0
	je ok
	and al,0xdf
	mov [str+edi],al
	mov eax,4
	mov ebx,1
	lea ecx,[str+edi]
	mov edx,1
	int 0x80
	inc edi
	jmp lp

ok:
	mov eax,1
	mov ebx,0
	int 0x80
