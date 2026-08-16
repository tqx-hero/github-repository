@echo off
cd /d "%~dp0"

:: 1. 汇编：去掉 -F dwarf，只用 -g 生成 stabs 格式调试信息
nasm -f win32 -g test.asm -o test.obj
if %errorlevel% neq 0 (
    echo NASM 编译失败！
    pause
    exit /b 1
)

:: 2. 链接：保留调试信息，-g 不能丢
ld -m i386pe -g -e _main test.obj -o test.exe
if %errorlevel% neq 0 (
    echo LD 链接失败！
    pause
    exit /b 1
)

echo 编译成功！test.exe 已带调试信息
pause