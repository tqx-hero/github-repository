#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc,char** argv){
	//使用当前用户查看文件的访问权限
	if(access(argv[1],R_OK) == -1)
		perror("access error");
	else
		printf("access success\n");
	if(open(argv[1],O_RDONLY) == -1)
		perror("open error");
	else 
		fprintf(stdout,"open success\n");
	return 0;
}
