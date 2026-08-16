section .text
global main
main:
	mov rdi,-8
	call abs_div2
	mov rdi,rax
	mov rax,60
	syscall
abs_div2:
	mov r8,2
	mov rax,rdi
	cmp rax,0
	jl convert_num
	
div_num:
	cqo
	idiv r8
	ret
convert_num:
	neg rax
	jmp div_num
