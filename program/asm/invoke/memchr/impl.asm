global asm_memchr
section .text
asm_memchr:
	push ebp
	push esi
	mov ebp,esp
	;字符串首地址
	mov esi,[ebp+12]
	;要匹配的字符
	mov al,[ebp+16]
	;字符串的长度
	mov ecx,[ebp+20]
	xor edx,edx
_begin_find:
	cmp edx,ecx
	;大于等于，没找到，返回0
	jge _no_find
	cmp byte [esi+edx],al
	;相同则找到了，返回地址
	je _find
	inc edx
	jmp _begin_find 

_find:
	lea eax,[esi+edx]
	jmp _end_func

_no_find:
	mov eax,0

_end_func:
	mov esp,ebp
	pop esi
	pop ebp
	ret
