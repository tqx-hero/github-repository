section .data
	msg: db "from asm: ",0
extern print_msg
global add_sum
section .text
add_sum:
	push ebp
	mov ebp,esp
	mov eax,dword [ebp+8]
	add eax,dword [ebp+12]
	push msg
	push eax
	call print_msg
	pop eax
	add esp,4
	mov esp,ebp
	pop ebp
	ret
