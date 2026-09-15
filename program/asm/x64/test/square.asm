section .text
global main
main:
	mov rdi,10
	call square
	mov rdi,rax
	mov rax,60
	syscall
	
square:
	mov rax,rdi
	imul rax,rax
	ret
