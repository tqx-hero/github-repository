#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
//将输入的参数写入文件,以fopen方式
int main(int argc,char** argv,char** env){
	if(argc ==1){
		fprintf(stderr,"请输入字符串\n");
		exit(-1);
	}
	FILE* fd = fopen("ftest.txt","w+");
	if(!fd){
		fprintf(stderr,"创建文件失败: %s\n",strerror(errno));
		exit(-1);
	}
	int i;
	for(i=1;i< argc;++i)
		fprintf(fd,"%s\n",argv[i]);
	fclose(fd);
	return 0;
}
