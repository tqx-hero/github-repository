#include <stdio.h>
//测试execve()系统调用执行输出
int main(int argc,char** argv,char** env){
	int i;
	for(i=1;i< argc;++i)
		fprintf(stdout,"argv[%d] = %s\n",i,argv[i]);
	while(*env){
		printf("%s\n",*env);
		env++;
	}
	return 0;
}
