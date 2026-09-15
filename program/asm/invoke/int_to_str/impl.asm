global asm_itoa
section .text
asm_itoa:
	push ebp
	push edi
	push esi
	push ebx
	mov ebp,esp
	sub esp,32
	;取出操作数与缓冲区首地址
	mov eax,[ebp+20]
	mov edi,[ebp+24]
	;设置栈首地址，用于存放余数
	lea esi,[ebp-32]	
	mov ebx,0xA
	;设置\0
	mov byte [esi],0
	mov ecx,1
get_remain:
	xor edx,edx
	div ebx
	;余数在edx，取余将其放到栈内
	add dl,'0'
	mov byte [esi+ecx],dl
	inc ecx
	;如果商为0，则退出压栈，开始往目标地址填充
	test eax,eax
	jnz get_remain
	dec ecx
	xor ebx,ebx
update_buf:
	cmp ecx,0
	;计数器小于0则退出
	jl _end_push
	mov al,[esi+ecx]
	mov [edi+ebx],al
	dec ecx
	inc ebx
	jmp update_buf

_end_push:
	mov esp,ebp
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
