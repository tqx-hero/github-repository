section .text
global main
main:
	call call_add
	mov rdi,rax
	mov rax,60
	syscall

add:
	push rbp
	mov rbp,rsp
	mov rax,[rbp+16]
	add rax,[rbp+24]
	mov rsp,rbp
	pop rbp
	ret

call_add:
	push rbp
	mov rbp,rsp
	push 20
	push 10
	call add

	mov rsp,rbp
	pop rbp
	ret
