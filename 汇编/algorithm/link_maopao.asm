section .data
	node6: dd 0,0
	node5: dd 19,node6
	node4: dd 9,node5
	node3: dd 28,node4
	node2: dd 6,node3
	node1: dd 15,node2
	;链表的节点个数
	len equ ($ - node5)/ 8
	buf: db 0
section .text
global _start
_start:
	;定义趟数，一共len-1趟
	mov ecx,1
begin_sort:
	cmp ecx,len
	;大于等于则排序结束
	jnl end_sort
	;小于则进行排序
	call sort_maopao
	;i++
	inc ecx
	jmp begin_sort
;内循环，排序函数
sort_maopao:
	push ecx
	push edx
	push esi
	push eax
	push ebx
	;找出起始节点，node1
	lea esi,[node1]
	;初始化j最大值(edx)与j(ecx)
	mov edx,len
	sub edx,ecx
	xor ecx,ecx	
;开始内循环
begin_j_sort:
	cmp ecx,edx
	;j >= len-i时，退出循环
	jnl break_sort
	;j<len-i时，执行排序
	;获取cur.val
	mov eax,[esi]
	;获取cur.next与cur.next.val
	mov edi,[esi+4]
	mov ebx,[edi]
	cmp eax,ebx
	;cur.val > cur.next.val，进行交换
	jg change_val
continue_sort:
	;指针前移，cur=cur.next
	mov esi,edi
	;j++
	inc ecx
	jmp begin_j_sort
	
;交换两个地址的数据
change_val:
	mov [esi],ebx
	mov [edi],eax
	jmp continue_sort

break_sort:
	pop ebx
	pop eax
	pop esi
	pop edx
	pop ecx
	ret

;结束排序，开始打印数据
end_sort:
	
	;找到根节点、next节点
	lea esi,[node1]
	xor ecx,ecx
	
loop_print:
	cmp ecx,len
	;大于长度时，结束打印
	jnl end_print
	;获取当前节点的数据，执行打印函数
	mov eax,[esi]
	call print_current_val
	call print_enter
	inc ecx
	mov esi,[esi+4]
	jmp loop_print
;需要额外打印一个换行符
end_print:
	mov eax,0xA
	call print_func
	jmp ok
	
print_current_val:
	push ecx
	push eax
	push edx
	mov ebx,0xA
	xor ecx,ecx
;将每个节点的数据压栈
push_val:
	xor edx,edx
	div ebx
	push edx
	inc ecx
	
	test eax,eax
	;eax为0时，压栈结束，开始打印当前值
	jz begin_print
	
	jmp push_val
;开始打印当前节点的数据
begin_print:
	pop eax
	;转ASCII
	add al,'0'
	call print_func
	dec ecx
	test ecx,ecx
	jnz begin_print
	
	pop edx
	pop eax
	pop ecx
	ret
;打印空格	
print_enter:
	push eax
	mov eax,32
	call print_func
	pop eax
	ret
;打印函数，打印字符与空格
print_func:
	push eax
	push ebx
	push ecx
	push edx
	
	mov [buf],al
	mov eax,4
	mov ebx,1
	mov ecx,buf
	mov edx,1
	int 0x80
	
	pop edx
	pop ecx
	pop ebx
	pop eax
	ret


ok:
	;先打印最大值到ebx看看
	mov ebx,[node5]
	mov eax,1
	int 0x80

