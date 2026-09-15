global asm_bubble
section .text

asm_bubble:
	push ebp
	push esi
	push ebx
	mov ebp,esp
	;设置3个局部变量，i，j，tmp
	sub esp,12
	;取出数组的首元素地址、数组长度
	mov esi,[ebp+16]
	mov ecx,[ebp+20]
	;设置局部变量趟数i起始值=1
	mov [ebp-4],1

_tangshu_func:
	cmp [ebp-4],ecx
	;如果大于等于长度，结束排序
	jnl end_sort
	;如果小于则计算比较次数edx
	mov edx,ecx
	sub edx,[ebp-4]
	;开始内循环，执行比较

	;设置比较起点j=0
	mov [ebp-8],0

begin_sort:
	cmp [ebp-8],edx
	jnl jmp_tangshu
	;开始比较
	mov ebx,[ebp-8]
	shl ebx,2
	;获取a[j],a[j+1]
	mov eax,[esi+ebx]
	cmp eax,[esi+ebx+4]
	jg change_number

continue_j:
	inc [ebp-8]
	jmp begin_sort

;交换a[j]与a[j+1]
change_number:
	;int tmp = a[j]
	mov [ebp-12],eax
	;eax = a[j+1]
	mov eax,[esi+ebx+4]
	;a[j] = a[j+1]
	mov [esi+ebx],eax
	;a[j+1] = tmp
	mov eax,[ebp-12]
	mov [esi+ebx+4],eax
	jmp continue_j
jmp_tangshu:

	;外循环的i++
	inc [ebp-4]
	jmp _tangshu_func



end_sort:

	
	mov esp,ebp
	pop ebx
	pop esi
	pop ebp
	ret
