global asm_call_func
section .text
asm_call_func:
	push ebp
	push esi
	mov ebp,esp
	;取出函数调用地址、操作数1、操作数2
	mov esi,[ebp+12]
	mov eax,[ebp+16]
	mov ecx,[ebp+20]
	;压栈调用函数,先压ecx、再压eax
	push ecx
	push eax
	call esi
	add esp,8
	mov esp,ebp
	pop esi
	pop ebp
	ret
