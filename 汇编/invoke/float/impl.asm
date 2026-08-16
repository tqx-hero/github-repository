global asm_circle_area
section .text
asm_circle_area:
	push ebp
	mov ebp,esp
	
	fld dword [ebp+8]
	fld dword [ebp+8]
	fmul
	fldpi
	fmul
	
	
	mov esp,ebp
	pop ebp
	ret