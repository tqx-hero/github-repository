section .text
global main
main:
	call local_summ
	mov rdi,rax
	mov rax,60
	syscall

local_summ:
	push rbp
	mov rbp,rsp
	sub rsp,32
	mov qword [rbp-8],30
	mov qword [rbp-16],20
	mov qword [rbp-24],0xA
	mov rax,[rbp-24]
	add rax,[rbp-16]
	add rax,[rbp-8]
	mov rsp,rbp
	pop rbp
	ret
