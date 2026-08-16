section .text
global _start
_start:
	mov eax,15
	mov ebx,20
	cmp eax,ebx
	jg big_call
	sub ebx,eax
	jmp ok

big_call:
	sub eax,ebx
	mov ebx,eax
ok:
	mov eax,1
	int 0x80
