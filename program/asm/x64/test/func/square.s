section .text
global main
main:
	mov rdi,3
	mov rsi,4
	call sum_squares
	mov rdi,rax
	mov rax,60
	syscall

sum_squares:
	push rbx

	mov rbx,rsi
	call square
	mov rdi,rbx
	mov rbx,rax
	call square
	add rax,rbx
	pop rbx
	ret

square:
	mov rax,rdi
	imul rax,rax
	ret
