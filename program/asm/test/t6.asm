section .data
	msg: db "hello,asm",0
section .text
global _start
_start:
	xor ebx,ebx
	lea esi,[msg]
	;xor eax,eax
lp:
	mov al,[esi]
	cmp al,0
	je ok
	inc ebx
	inc esi
	jmp lp
ok:
	mov eax,1
	int 0x80
