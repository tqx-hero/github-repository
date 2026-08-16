section .data
	msg: db "hello,asm",0
	len equ $-msg-1
section .text
global _start
_start:
	lea esi,[msg]
	
	lea edi,[msg+len-1]
reverse_str:
	cmp esi,edi
	jge ok
	mov al,[esi]
	mov bl,[edi]
	mov  [esi],bl
	mov  [edi],al
	inc esi
	dec edi
	jmp reverse_str
ok:
	;打印字符串
	mov eax,4
	mov ebx,1
	mov ecx,msg
	mov edx,len+1
	int 0x80	

	mov eax,1
	mov ebx,len
	int 0x80
