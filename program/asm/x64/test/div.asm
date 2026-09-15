section .text
global main
main:
	mov rdi,200
	call div_func
	mov rdi,rax
	mov rax,60
	syscall
div_func:
	mov rcx,2
	mov rax,rdi
	cqo
	idiv rcx
	ret
