;判断字符串是否是回文串
section .data
	msg: db "levnavel",0
	len equ $ - msg -1
section .text
global _start
_start:
	lea esi,[msg]
	lea edi,[msg+len-1]
	
is_huiwen:
	cmp esi,edi
	jnl yes_huiwen
	mov al,[esi]
	and al,0xdf
	mov bl,[edi]
	and bl,0xdf
	cmp al,bl
	jne no_huiwen
	inc esi
	dec edi
	jmp is_huiwen
yes_huiwen:
	mov ebx,1
	jmp ok
;不是回文串，添加ebx退出码为0
no_huiwen:
	mov ebx,0
ok:
	mov eax,1
	int 0x80
