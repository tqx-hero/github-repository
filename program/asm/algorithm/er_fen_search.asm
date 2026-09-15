section .data
	arr: dd 7,12,23,45,56,89
	len equ ($ -arr)/4
	target: dd 45
section .text
global _start
_start:
	;定义左右指针left:esi; right:edi
	mov esi,0
	mov edi,len-1
	;目标数放到edx
	mov edx,[target]
lp0:
	cmp esi,edi
	;大于，说明没找到，返回
	jg no_find_ok
	;小于等于，则开始寻找
	;计算middle下标放入eax
	mov eax,edi
	sub eax,esi
	shr eax,1
	add eax,esi
	cmp [arr+eax*4],edx
	;如果等于目标数，直接返回
	je find_ok
	;如果大于目标数，right指针等于middle-1
	jg fix_right_ptr
	;如果小于目标数，left=middle+1
	jl fix_left_ptr
	;如果以上情况都没有，则出现异常
	jmp no_find_ok
;小于目标数，移动left=middle+1
fix_left_ptr:
	lea esi,[eax+1]
	jmp lp0
;大于目标数，右指针等于middle-1
fix_right_ptr:
	lea edi,[eax-1]
	jmp lp0
;找到时的处理函数
find_ok:
	mov ebx,eax
	jmp ok

;没找到时的处理函数
no_find_ok:
	mov ebx,0xff
	jmp ok

;返回函数
ok:
	
	mov eax,1
	int 0x80
