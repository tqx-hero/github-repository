;定义结构体
struc Student
	.id resw 1
	.name resb 16
	.score resd 1
endstruc

section .data
;全局变量
stu1: 
	istruc Student 
		at Student.id, dw 2
		at Student.name, db 'abcd'
		at Student.score, dd 10
	iend
	
buf: db 0

section .text
global _start
_start:
	lea esi,[stu1]
	mov word [esi+Student.id],20
	mov byte [esi+Student.name],'A'
	mov byte [esi+Student.name+1],'B'
	mov dword [esi+Student.score],200

;print_name:
	


	mov eax,1
	mov ebx, [esi+Student.id]
	int 0x80