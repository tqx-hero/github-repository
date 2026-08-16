section .text
global main
main:
	mov rdi,2
	mov rsi,3
	call calc
	mov rdi,rax
	mov rax,60
	syscall
calc:
	imul rdi,rdi,2
	imul rsi,rsi,3
	add rdi,rsi
	mov rax,rdi
	ret
