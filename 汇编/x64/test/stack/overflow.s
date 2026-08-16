section .text
global main
main:
	call vuln
	mov rdi,66
	jmp exit


exit:
	mov rax,60
	syscall

shell:
	mov rdi,88
	jmp exit

vuln:
	push rbp
	mov rbp,rsp
	sub rsp,8
	mov qword [rbp-8],10
	lea rdi,[rel shell]
	mov qword [rbp+8],rdi
	mov rsp,rbp
	pop rbp
	ret
