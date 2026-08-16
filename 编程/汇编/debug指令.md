### debug指令：

1. 挂载debug.exe所在的目录:

   ###### 	格式： mount  C（虚拟盘，也可以为D） debug.exe所在的目录

   ```assembly
   - mount c D:\DOS
   ```

2. 查看虚拟盘下的所有文件：

   ​	

   ```assembly
   - dir
   ```

   

3. 执行debug。直接输入debug。

4. R命令查看CPU寄存器中的内容。

   ​	

   ```assembly
   - r
   ```

   ![效果图](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501191002787.png)

5. 改变对应寄存器中的数据：

   ###### 	格式为：r 寄存器名称，如修改ax寄存器中的数据为0xED23，则：

   ```assembly
   - r ax 
   - ED23
   ```

   ![image-20260501191404206](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501191404206.png)

6. D命令查看指定内存地址的字节内容：

   ###### 	例：查看起始位置为2000:0的后128个字节的内容：

   ```assembly
   -d 2000:0
   ```

   ![image-20260501191859483](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501191859483.png)

   ###### 	查看从2000:0 到2000:10区间内的字节内容：

   ```assembly
   -d 2000:0 10
   ```

   ![image-20260501192039770](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501192039770.png)

7. E命令修改指定字节的数据：

   ###### 例：修改2000:0处的数据为ff:

   ```assembly
   -e 2000:0
   -    ff
   ```

   ![image-20260501192610976](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501192610976.png)

   ###### 修改从2000:0开始往后的数据：(第二行的.前面的数据为这个字节中的原始内容，.后面的为修改后的数据。空格可以进行连续的修改，回车表示修改完成)

   ```assembly
   -e 2000:0
   ff.ee(输入后空格) 00.aa(输入后空格) 00.13(输入后空格) ....回车确定修改完成
   ```

   ![image-20260501192954208](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501192954208.png)

   ###### 从2000:0开始修改多个数据：

   ```assembly
   -e 2000:0 dd 22 33 44 55 ...回车确认输入
   ```

   ![image-20260501193413690](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501193413690.png)

8. U命令查看所在地址的汇编指令：

   ###### 查看2000:0所在字节的汇编指令(以下汇编指令是上一个示例输入的代码翻译过来的，注意这里的机器是小端序存储，上方示例输入的2301，翻译回来是0123)：

   ```assembly
   -u 2000:0
   ```

   ![image-20260501193606597](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501193606597.png)

9. A命令写入汇编代码：

   ###### 往CS:IP中写入如下汇编代码：

   ```assembly
   mov ax,0123
   mov bx,0003
   mov ax,bx
   add ax,bx
   ```

   则：

   ###### 	找到CS:IP所在的位置：

   ```assembly
   -a 073f:100
   mov ax,0123
   mov bx,0003
   mov ax,bx
   add ax,bx
   敲两次回车确认
   ```

   ![image-20260501194334926](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501194334926.png)

10. T执行汇编代码：

    ###### 执行CS:IP所在寄存器的汇编代码：

    ```assembly
    -t
    -t
    ...
    直到代码执行完成
    ```

    ![image-20260501194613216](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20260501194613216.png)

11. Q退出debug模式：

    ```assembly
    -q
    ```

12. R修改寄存器地址：

    ###### 修改CS地址为0x2000，IP地址为0x0000：

    ```assembly
    -rcs
    -2000
    -rip
    -0
    ```

13. jmp命令实现指令执行的跳转：

    ###### jmp 段地址:偏移地址。此种方式可直接修改CS:IP两个寄存器中的地址，进而实现代码执行的跳转

    ###### 以下为将CS:IP中的地址修改为2000:0000

    ```assembly
    -jmp 2000:0
    ```

    ###### jmp 偏移地址，此种方式是只修改IP寄存器内的数据，即只修改偏移地址

14. 