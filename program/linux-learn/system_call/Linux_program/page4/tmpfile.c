#include <stdio.h>
#include <unistd.h>
//tmpfile()函数的用法
int main(){
	FILE* file;
	if(!(file = tmpfile())){
		perror("create tempfile error");
		return -1;
	}
	printf("创建临时文件成功\n");
	fclose(file); //可选择关闭，如果进程退出也会自动回收该临时文件，所以flose为可选
	return 0;
}
