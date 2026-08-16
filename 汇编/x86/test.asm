section .text
global main
main:
    mov ebp, esp; for correct debugging
    ; 1. 建立栈帧，方便调试
    push ebp
    mov ebp, esp

    ; 你的核心指令
    mov eax, 0FFh     ; eax = 0x000000FF
    mov ebx, eax    ; ebx = 0x000000FF

    ; 2. 正常退出程序（Windows 兼容，用 C 库 exit 函数）
    push 0          ; 退出码 0
    call exit@4     ; 调用 exit 函数，带 4 字节参数

    ; 3. 恢复栈帧（调试用）
    mov esp, ebp
    pop ebp
    ret