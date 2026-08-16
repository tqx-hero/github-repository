section .data
  das: dd 3,4,5,0
section .text
global _start
_start:
	mov eax,[das]
	mov ebx,[das+4]
	mov ecx,[das+8]
	mov edx,[das+12]
	cmp eax,ebx
	je adda
	cmp eax,ecx
	je addc
	mov edx,1
	jmp exit_call

adda:
	add edx,ebx
	jmp exit_call
addc:
	mov edx,ecx
exit_call:
	mov eax,1
	mov ebx,0
	int 0x80
