global asm_hex2int
section .data
;设置哈希表,以ASCII码值为index，value为代表的数字
	hash: 
		db 48 dup(0)
		db 0,1,2,3,4,5,6,7,8,9
		db 7 dup(0)
		db 10,11,12,13,14,15
section .text
asm_hex2int:
	push ebp
	mov ebp,esp
		
	mov cl,[ebp+8]
	cmp cl,48
	;小于48不合法
	jl _illegal
	;大于70不合法
	cmp cl,70
	jg _illegal
	;小于等于57的，查表
	cmp cl,57
	jle search_hash
	;大于等于65，查表
	cmp cl,65
	jge search_hash
	;除此之外都不合法
	jmp _illegal
search_hash:
	xor eax,eax
	movzx edx,cl
	mov al,byte [hash+edx]
	jmp _ret
_illegal:
	mov eax,-1
	jmp _ret
_ret:
	mov esp,ebp
	pop ebp
	ret
