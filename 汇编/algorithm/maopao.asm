section .data
	arr: dd 12,45,7,89,23,56
	len equ ($ - arr) /4
section .text
global _start
_start:
	mov ecx,len-1
	mov edx,1
tangshu:
	cmp ecx,edx
	;小于时退出循环
	jb ok
	;大于等于时，执行循环
	call nei_xun_huan
	inc edx
	jmp tangshu

nei_xun_huan:
	push edx
	push ebx
	push eax
	push esi
	push ecx
	;求内循环的最大数
	mov ebx,len-1
	sub ebx,edx
	;设置起始点	
	mov esi,0
	
_xun_huan:
	;比较条件
	cmp esi,ebx
	jg end_nei_xun_huan
	;对每一趟的相邻数据比较，大的交换
	lea ecx,[arr+esi*4]
	mov eax,[ecx]
	mov edx,[ecx+4]
	cmp eax,edx
	;如果大于后面的数，则需要交换
	jg change_data
inc_esi:
	;自增地址
	inc esi
	jmp _xun_huan
end_nei_xun_huan:
	pop ecx
	pop esi
	pop eax
	pop ebx
	pop edx
	ret
;交换两者数据
change_data:
	mov [ecx],edx
	mov [ecx+4],eax
	jmp inc_esi 

ok:
	shl ecx,2
	mov ebx,[arr+ecx]
	mov eax,1
	int 0x80
