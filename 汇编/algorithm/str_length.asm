section .data
	str: db "Assembly Code",0
section .text
global _start
_start:
	lea esi,[str]
	xor ecx,ecx
	
lp:
	mov al,[esi]
	;查看数据是否为0
	test al,al
	;为0则退出程序
	jz end_lp
	inc ecx
	inc esi
	jmp lp
end_lp:
	mov ebx,ecx
	mov eax,1
	int 0x80
