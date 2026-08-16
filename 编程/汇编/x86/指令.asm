section .text
global main
main:
	movzx eax, byte ptr [edx] 	;0扩展
	movsx eax,byte ptr [edx] 	;符号扩展
	mov ebx,5
	and eax,ebx
	or ebx,eax
	xor ecx,edx
	test eax,eax	;不改变寄存器值的情况下判断寄存器数据是否为0，如果为0，ZF=1;不为0,ZF = 0
	jz	ok			;如果寄存器数据为0，则跳转
	mul ebx			;寄存器数据相乘，高位放edx，低位放eax： edx:eax = eax*ebx
	div ebx			;寄存器相除，余数在edx，商在eax：	eax Redx = edx:eax /ebx
	
	;标志位寄存器flag
	;	CF	: 最高位进位或借位，add时进位、sub时借位，CF=1，没有进位借位CF=0
	;	OF	：溢出位。两个大正数或者两个小负数相加可能会溢出，OF=1，没有溢出OF=0
	;	ZF	:零标志位，结果为0，ZF=1，不为0，ZF=0
	;	SF	：是否是负数。是负数，SF=1，不是负数SF=0
	;	PF	:奇偶校验位，有偶数个1，PF=1，奇数个PF=0
	
	;跳转指令
	jmp ok	;无条件跳转
	
	;-----------------以下判断都可以在j后面加n，表示反面意思---------------------------------
	jz ok	;结果等于0，即ZF=1时，跳转
	jnz	ok ;结果不等于0，即ZF=0时跳转
	je	ok	;比较结果相等时，等同于jz，跳转
	jne	ok	;比较结果不相等，等同于jnz，跳转
	jc ok 	;检验进位借位标志位carry =1时，跳转
	jnc ok ;carray =0,没有进位借位时跳转
	jo ok	;检验溢出标志位OF，溢出时即OF=1跳转
	jno ok ;没有溢出跳转
	js ok	;检验符号位SF =1，即为负数时跳转
	jns ok ;不为负数，SF=0时跳转
	jp	ok ;检验奇偶校验位，PF=1时，即有偶数个1，跳转
	jnp	ok	;PF=0，有奇数个1时跳转
	
	jg	ok	;有符号数的比较，greater，大于的时候跳转
	jge	ok	;有符号数比较，大于等于跳转
	jl	ok	;有符号数比较，low，小于跳转
	jle	ok	;有符号数比较，小于等于跳转
	
	ja	ok	;无符号数比较，above，大于时跳转
	jae	ok	;无符号数，大于等于跳转
	jb	ok	;无符号数比较，小于跳转
	jbe	ok	;无符号数，小于等于跳转
	
	call ok	;函数调用，调用前把当前指令的下一条指令的地址入栈，保存现场，当ret时，弹栈还原eip的值，即恢复现场
	
	ret	;返回指令，与call逻辑互补，调用时pop eip，同时esp+=4
	ret 4	;返回指令，在pop eip并esp+=4之后，继续使esp+=4个字节，相当于直接丢弃4个字节的无用数据
	
	cmp eax,ebx		;比较eax与ebx的值，结果= eax-ebx，后续可根据以上的众多判断逻辑进行相应的跳转
	
	;移位运算
	shr ebx,2	;逻辑右移2位，高位补0，移出的低位放到CF
	shl ebx,2	;逻辑左移2位，低位补0，移出的高位放到CF
	sar ebx,2	;算术右移2位，高位补符号，移出的低位放到CF
	
ok:
	mov edx,10