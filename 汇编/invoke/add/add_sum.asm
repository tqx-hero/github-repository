global asm_add
extern printf
section .data
	msg: db "add result = %d ",0xA,0
section .text
asm_add:
	push ebp
	mov ebp,esp
	mov eax,dword [ebp+8]
	add eax,dword [ebp+12]
	push eax
	push msg
	call printf
	add esp,4
	pop eax
	mov esp,ebp
	pop ebp
	ret 

