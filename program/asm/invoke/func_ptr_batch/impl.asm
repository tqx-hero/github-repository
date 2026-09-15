global asm_call_all
extern printf
section .data
	msg: db "res = %d",0xA,0
section .text
asm_call_all:
	push ebp
	push edi
	push ebx
	mov ebp,esp
	sub esp,32
	;函数数组首元素地址
	mov edi,[ebp+16]
	;函数指针数组长度,存放在[ebp-32]
	mov ebx,[ebp+20]
	;操作数a,存放位置：[ebp-32]
	mov eax,[ebp+24]
	mov dword [ebp-32],eax
	;操作数b,存放到[ebp-28]
	mov eax,[ebp+28]
	mov dword [ebp-28],eax
	xor ecx,ecx
	;[ebp-20]单元存放计数
	mov dword [ebp-24],ecx
_loop_call:
	mov ecx,dword [ebp-24]
	;比较数组最大长度，大于等于则停止调用
	cmp ecx,ebx
	jge _end_call
	;先压操作数b、再压操作数a
	push dword [ebp-28]
	push dword [ebp-32]
	shl ecx,2
	call [edi+ecx]
	add esp,8
	;调用打印
	push eax
	push msg
	call printf
	add esp,8
	
	inc dword [ebp-24]
	jmp _loop_call
_end_call:
	mov esp,ebp
	pop ebx
	pop edi
	pop ebp
	ret