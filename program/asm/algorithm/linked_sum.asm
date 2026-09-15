section .data
	;尾结点
	node5: 
		dd 0
	        dd 0
	node4:
		dd 9
		dd node5
	node3:
		dd 12
		dd node4
	node2:
		dd 7
		dd node3
	node1:
		dd 3
		dd node2
	node0:
		dd 0
		dd node1
section .text
global _start
_start:
	;加载哨兵节点地址到esi
	lea esi,[node0]
	xor ebx,ebx
lp:
	;查看next指针是否为0，为0则停止
	mov edi,[esi+4]
	test edi,edi
	jz end_sum
	;next指针不为0，则跳转到next指向的地址
	lea esi,[edi]
	;取出数据，数据为esi所在地址的低4字节
	add ebx,[edi]
	jmp lp
end_sum:
	mov eax,1
	int 0x80

