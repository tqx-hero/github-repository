section .text
global _start
_start:
	mov eax,40
	mov ebx,100

	push eax
	push ebx
	call add_func
	add esp,8
	;结果放到ebx
	mov ebx,eax
	mov eax,1
	int 0x80

add_func:
	push ebp
	mov ebp,esp
	;设置栈帧大小为4字节
	sub esp,16
	lea esi,[ebp-4]
	mov eax,dword [ebp+12]
	mov [esi],eax
	mov ebx,dword [ebp+8]
	add [esi],ebx
	mov eax,[esi]
	mov esp,ebp
	pop ebp
	ret
