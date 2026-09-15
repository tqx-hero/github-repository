section .data
	arr: dd 1,2,3,4,5
	len dq 5
section .text
global main
main:
	mov rdi,arr
	mov rsi,[rel len]
	call sum_array
	mov rdi,rax
	mov rax,60
	syscall
sum_array:
	xor r8,r8
	xor rax,rax
begin_lp:
	cmp r8,rsi
	;下标大于等于长度，结束
	jge end_lp
	add eax,[rdi]
	add rdi,4
	inc r8
	jmp begin_lp

end_lp:
	ret
