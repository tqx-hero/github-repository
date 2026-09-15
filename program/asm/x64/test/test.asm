section .text
global main

main:
	mov rdi,10
	mov rsi,20
	call add
	mov rdi,rax
	mov rax,60
	syscall
add:
	mov rax,rdi
	add rax,rsi
	ret
	
