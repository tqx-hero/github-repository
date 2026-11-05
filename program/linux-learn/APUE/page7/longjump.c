#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
//使用setjmp(3)、longjump(3)实现非局部跳转，也就是栈帧之间跳转
jmp_buf jb;
int cnt;
static int num;
void f1(){
	fprintf(stdout,"f1() ...\n");
	longjmp(jb,1);
}

void f2(){
	fprintf(stdout,"f2() ...\n");
	longjmp(jb,2);
}

int main(){
	int ret;
	volatile int autonum = 100;
	cnt += 20;
	num = 30;
	if(!(ret = setjmp(jb))){
		//刚执行setjmp(3)保存现场,longjmp(3)还未被调用,返回值等于0
		fprintf(stdout,"into the func...\n");
		cnt += 1;
		num += 1;
		autonum += 1000;
		f1();
	}else if(ret == 1){//从longjmp(3)设置值1那里跳转过来
		fprintf(stdout,"从1那里跳转过来的...\n");
		f2();
	}else {
		fprintf(stdout,"从2那里跳转过来的..\n");
	}
	fprintf(stdout,"正在退出...\n");
	fprintf(stdout,"cnt = %d,num = %d,autonum = %d\n",cnt,num,autonum);
	exit(0);
}
