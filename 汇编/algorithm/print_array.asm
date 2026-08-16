section .data
	arr: dd 18,99,256,310,47
	len equ ($ - arr)/4
	buf: db 0
section .text
global _start
_start:
	
	lea esi,[arr+(len-1)*4]
	push 0xA
	mov ecx,1
init_data:
	cmp esi,arr
	jb pop_data
	;数据加载到eax,计数器清零
	mov eax,[esi]
	mov ebx,0xA
	
;数据压栈
push_stack:
	xor edx,edx
	test eax,eax
	;数据为0，压栈结束,压入空格，指针前移
	jz next_init
	;不为0，算除数，取余数
	div ebx
	push edx
	inc ecx
	jmp push_stack

next_init:
	;压入空格
	push 32
	inc ecx
	;指针前移
	sub esi,4
	jmp init_data
	
;往外弹数据
pop_data:
	add esp,4
	dec ecx
	mov esi,ecx
start_pop:
	pop eax
	dec esi
	;判断是否是空格，是的话不需要转换成ASCII
	cmp al,10
	jl trans_ascii  
	
print_datas:
	mov [buf],al
	mov eax,4
	mov ebx,1
	mov edx,1
	mov ecx,buf
	int 0x80
	
	;判断是否打印完成，完成后打印换行符
	test esi,esi
	jz end_print
	jmp start_pop
;数字转换成ASCII码
trans_ascii:
	add al,'0'
	jmp print_datas
;结束打印，补上换行打印
end_print:
	;结束打印
	mov eax,1
	mov ebx,0
	int 0x80
	
