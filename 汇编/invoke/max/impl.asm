global asm_max3

section .text
asm_max3:
	push ebp
	mov ebp,esp
	
	mov eax,[ebp+8]
	mov ecx,[ebp+12]
	xor edx,edx
	cmp ecx,eax
	jg change_num
_ctn:	
	inc edx
	cmp edx,2
	jge _end_cmp 
	mov ecx,[ebp+16]
	cmp ecx,eax
	jg change_num
	jmp _end_cmp 
change_num:
	mov eax,ecx
	jmp _ctn
_end_cmp:
	mov esp,ebp
	pop ebp
	ret
