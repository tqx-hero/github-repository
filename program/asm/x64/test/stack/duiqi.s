section .text
global main
main:
	call aligned_test
	mov rdi,rax
	mov rax,60
	syscall

aligned_test:
	push rbp
	push rbx
	push r12
	push r13
	mov rbp,rsp
	sub rsp,24
	mov qword [rbp-8],200
	mov qword [rbp-16],100
	mov rax,[rbp-16]
	add rax,[rbp-8]
	mov rsp,rbp
	pop r13
	pop r12
	pop rbx
	pop rbp
	ret



