section .text
global main
main:
	call local_sum
	mov rdi,rax
	mov rax,60
	syscall

local_sum:
	push rbp
	mov rbp,rsp
	sub rsp,16
	mov qword [rbp-8],7
	mov qword [rbp-16],13
	mov rax,[rbp-8]
	add rax,[rbp-16]
	mov rsp,rbp
	pop rbp
	ret
