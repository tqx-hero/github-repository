#include <stdio.h>
#include <stdlib.h>
#define PERROR_EXIT(__ERRMSG) perror(__ERRMSG); \
    				goto fail_ret
//使用标准I/O函数拷贝文件
int main(int argc,char** argv){
	FILE *srcf = NULL,*dstf = NULL;
	int ch;
   	if(argc < 3){
		fprintf(stderr,"请输入文件名!\n");
		exit(EXIT_FAILURE);
	}
	//打开文件
	if((srcf = fopen(argv[1],"r")) == NULL){
	    PERROR_EXIT("open src error");
	}
	if((dstf = fopen(argv[2],"w")) == NULL){
	    PERROR_EXIT("open dst error");
	}
	//开始读取，写入
	while((ch = getc(srcf)) != EOF)
	    putc(ch,dstf);
	fclose(dstf);
	fclose(srcf);
	return 0;

fail_ret:
	if(srcf)
	    fclose(srcf);
	if(dstf)
	    fclose(dstf);
	exit(EXIT_FAILURE);
}
