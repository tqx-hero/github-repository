global asm_sort
;定义宏：返回
%macro RET_FUNC 0
	mov esp,ebp
	pop edi
	pop esi
	pop ebx
	pop ebp
	ret
%endmacro
;定义宏：压栈保护现场
%macro PUSH_REGISTERS 0
	push ebp
	push ebx
	push esi
	push edi
	mov ebp,esp
%endmacro

%macro CMP_I_J 0
	mov eax,dword [ebp-56]
	mov edx,dword [ebp-52]
	cmp eax,edx
	jg _change_num
%endmacro

;调用函数方式。注意展开时下标从1开始取
%macro CALL_FUNC_FORMAT3 4
	push %1
	push %2
	push %3
	call %4
	add esp,12
%endmacro

%macro GET_PARAM3 3
	mov %1,[ebp+20]
	mov %2,[ebp+24]
	mov %3,[ebp+28]
%endmacro

section .text
asm_sort:
	PUSH_REGISTERS
	sub esp,64
	;取参数,数组地址
	mov edi,[ebp+20]
	;数组长度
	mov eax,[ebp+24]
	mov dword [ebp-64],eax
	cmp eax,1
	jle _direct_ret
	dec eax
	;压入(int a[],begin,end)

	CALL_FUNC_FORMAT3 eax,0,edi,_sort_fast 
	jmp _direct_ret

_sort_fast:
	PUSH_REGISTERS
	
	sub esp,64
	;取参数，分别为：(int a[],begin,end)
	GET_PARAM3 edi,eax,ecx
	;begin >end ,return
	cmp eax,ecx
	jg _direct_ret
	;将数据存入栈内局部变量
	;[ebp-64] = begin
	mov dword [ebp-64],eax
	;[ebp-60] = end
	mov dword [ebp-60],ecx
	inc eax
	;[ebp-56]=i
	mov dword [ebp-56],eax
	;[ebp-52] = j
	mov dword [ebp-52],ecx
	mov eax,[edi]
	;取出第一个数据cmp
	mov dword [ebp-48],eax
	
_loop_sort:
	CMP_I_J
	
_loop_i:
	CMP_I_J
	mov ebx,eax
	shl ebx,2
	;取出a[i]
	mov ecx,[edi+ebx]
	;a[i]<cmp,i++，否则跳出循环
	cmp ecx,dword [ebp-48]
	jge write_loop_j
	inc dword [ebp-56]
	jmp _loop_i
;写回i的值，结束循环并跳转到循环查找j
write_loop_j:
	
	jmp _loop_j
;
_loop_j:
	CMP_I_J
	mov ebx,edx
	shl ebx,2
	;取出a[j]
	mov ecx,[edi+ebx]
	;a[j]>cmp,j--,否则跳出循环
	cmp ecx,dword [ebp-48]
	jle write_j_change
	dec dword [ebp-52]
	jmp _loop_j
;写回j的值，并且准备交换两个内存中的数据
write_j_change:
	CMP_I_J
	;如果i<=j
	;压栈：(i,j,a[])
	
	CALL_FUNC_FORMAT3 edi,dword [ebp-52],dword [ebp-56],_swap
	;i++,j--
	inc dword [ebp-56]
	dec dword [ebp-52]
	jmp _loop_sort
;交换begin与--i的数据	
_change_num:
	;压栈：(begin,--i,a)
	dec dword [ebp-56]

	CALL_FUNC_FORMAT3 edi,dword [ebp-56],dword [ebp-64],_swap
	;递归调用函数
	mov ebx,dword [ebp-56]
	sub ebx,1
	;sortByDi(a, begin, i - 1)
	CALL_FUNC_FORMAT3 ebx,dword [ebp-64],edi,_sort_fast
	;sortByDi(a, i + 1, end)
	add ebx,2
	CALL_FUNC_FORMAT3 dword [ebp-60],ebx,edi,_sort_fast
	
	jmp _direct_ret

;交换2者数据，格式为swap(i,j,a[])	
_swap:
	PUSH_REGISTERS
	;i,j,a[]
	GET_PARAM3 eax,ecx,edi
	shl eax,2
	;a[i]
	mov edx,[edi+eax]
	;a[j]
	shl ecx,2
	mov ebx,[edi+ecx]
	mov dword [edi+eax],ebx
	mov dword [edi+ecx],edx
	
_direct_ret:
	RET_FUNC