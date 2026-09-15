section .data
	arr: dq 1,-2,3,-4,5,-6
	len equ ($-arr)/8
section .text
global main
main:
	mov rdi,arr
	mov rsi,len
	call sum_positive
	mov rdi,rax
	mov rax,60
	syscall
sum_positive:
	xor r8,r8
	xor rax,rax

begin_sum:
	cmp r8,rsi
	jge end_sum
	mov rcx,[rdi]
	cmp rcx,0
	jle go_next
	add rax,[rdi]
go_next:
	add rdi,8
	inc r8
	jmp begin_sum
end_sum:
	ret
