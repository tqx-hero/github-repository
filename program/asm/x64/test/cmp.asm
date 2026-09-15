section .text
global main
main:
	mov rdi,10
	mov rsi,-3
	call _max
	mov rdi,rax
	mov rax,60
	syscall
_max:
	cmp rdi,rsi
	jge mov_rdi
	mov rax,rsi
_end:
	ret
mov_rdi:
	mov rax,rdi
	jmp _end