section .data
	num: dd 10,3
	op: db '+'
section .text
global _start
_start:
	mov eax,[num]
	mov ebx,[num+4]
	mov cl,[op]
	cmp cl,'+'
	je add_nums
	cmp cl,'-'
	je sub_nums
	xor edx,edx
	cmp cl,'*'
	je mul_nums
	cmp cl,'/'
	div ebx
	mov ebx,eax
	jmp ok
	;其他的运算符，直接返回0
	mov ebx,0
	jmp ok
add_nums:
	add ebx,eax
	jmp ok
sub_nums:
	sub eax,ebx
	mov ebx,eax
	jmp ok
mul_nums:
	mul ebx
	mov ebx,eax	
ok:
	mov eax,1
	int 0x80
