global asm_count_bits
section .text
asm_count_bits:
	push ebp
	push ebx
	mov ebp,esp
	
	mov eax,[ebp+12]
	xor ebx,ebx
_cal_bits:
	mov ecx,eax
	and ecx,1
	test ecx,ecx
	;如果ecx为0，那么个位为0，继续
	jnz add_count

_ctn:
	shr eax,1
	test eax,eax
	jz _end_call
	jmp _cal_bits
add_count:
	inc ebx
	jmp _ctn

_end_call:
	mov eax,ebx
	mov esp,ebp
	pop ebx
	pop ebp
	ret
