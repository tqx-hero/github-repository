extern printf
global main
section .data
	msg: db "The number is: %d",0xA,0
section .text


main:
	push ebp
	mov ebp,esp

	push 2025
	push msg
	call printf
	add esp,8
	mov eax,0
	mov esp,ebp
	pop ebp
	ret

