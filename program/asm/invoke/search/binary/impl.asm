global asm_binary_search
%macro PUSH_REGISTERS 0 
	push ebp
	push ebx
	push edi
	push esi
	mov ebp,esp
%endmacro

%macro RET_POP 0
	mov esp,ebp
	pop esi
	pop edi
	pop ebx
	pop ebp
	ret
%endmacro
section .text
asm_binary_search:
	PUSH_REGISTERS
	sub esp,64
	mov esi,[ebp+20]
	mov eax,[ebp+24]
	mov ecx,[ebp+28]
	;arr[]
	mov dword [ebp-64],esi
	;len
	mov dword [ebp-60],eax
	;target
	mov dword [ebp-56],ecx
	;begin
	mov dword [ebp-52],0
	;end
	dec eax
	mov dword [ebp-48],eax
	
	mov edi,dword [ebp-56]
_find_num:
	mov eax,dword [ebp-52]
	mov ecx,dword [ebp-48]
	cmp eax,ecx
	;begin >end
	jg no_find
	;(right-left)>>1
	sub ecx,eax
	shr ecx,1
	add eax,ecx
	;mid
	mov edx,eax
	shl eax,2
	;a[mid]
	mov ebx,[esi+eax]
	cmp ebx,edi
	je yes_find
	;a[mid]>target,end = mid-1
	jg sub_end
	;a[mid]<target,begin=mid+1
	inc edx
	mov dword [ebp-52],edx
	jmp _find_num

sub_end:
	dec edx
	mov dword [ebp-48],edx
	jmp _find_num
	
;找到了	
yes_find:
	mov eax,edx
	jmp _ret
;没找到
no_find:
	mov eax,-1
_ret:
	RET_POP