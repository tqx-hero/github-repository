#include <stdio.h>
#include <unistd.h>

//验证标准I/O的缓冲区问题，系统调用没有缓冲区直接写入
//标准I/O存在缓冲区，行缓冲或缓冲区满了才会写入.
//只有在关闭流的缓冲区，或者使用fflush及时冲刷缓冲区，才不会造成数据错乱
int main(){
	setvbuf(stdout,NULL,_IONBF,0);
	putchar('a');
	write(1,"b",1);

	putchar('a');
	write(1,"b",1);

	putchar('a');
	write(1,"b",1);
	return 0;
}
