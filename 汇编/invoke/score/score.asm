global asm_find_max
extern print_max
section .text
asm_find_max:
	push ebp
	push esi
	push edi
	push ebx
	mov ebp,esp
	;1、开辟存放最大值结构体地址的空间
	;2、数组元素数量
	sub esp,12
	;[ebp-4]存放数组首地址
	;[ebp-8]存放数组元素个数
	mov esi,[ebp+20]
	mov [ebp-4],esi
	mov ecx,[ebp+24]
	mov [ebp-8],ecx
	dec ecx 
	mov ebx,20
begin_cmp:
	cmp ecx,0
	;如果下标<0，结束统计结果
	jl end_cmp
	;获取这个结构体中的分数
	;edi为这个结构体的首地址
	mov eax,ecx
	mul ebx
	lea edi,[esi+eax]
	mov eax,[edi+16]
	cmp eax,[ebp-12]
	jg update_max

continue_cmp:
	dec ecx
	jmp begin_cmp

;分数大于当前最大值，需要更新
update_max:
	mov [ebp-12],eax
	mov [ebp-4],edi
	jmp continue_cmp
	
;统计结果调用C输出函数
end_cmp:

	;把分数压入栈内
	push dword [ebp-12]
	;把名字首地址压入栈内，需要压4次
	push dword [ebp-4]
	call print_max
	add esp,8
	mov eax,[ebp-12]
	mov esp,ebp
	pop ebx
	pop edi
	pop esi
	pop ebp
	ret
