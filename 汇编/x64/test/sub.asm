section .text
global main

main:
	mov rdi,30
	mov rsi,20
	call muls
	mov rdi,rax
	mov rax,60
	syscall

muls:
	mov rax,rdi
	sub rax,rsi
	ret
