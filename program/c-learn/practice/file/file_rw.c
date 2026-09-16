#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char** argv,char** env){
	if(argc != 3){
		fprintf(stderr,"参数不够\n");
		exit(-1);
	}
	FILE* r_fd = fopen(argv[1],"r");
	FILE* w_fd = fopen(argv[2],"w+");
	if(!r_fd || !w_fd){
		fprintf(stderr,"文件打开失败\n");
		if(r_fd)
			fclose(r_fd);
		if(w_fd)
			fclose(w_fd);
		exit(-1);
	}
	char message_buf[1024];
	ssize_t len;
	//读取文件到另一个文件
	while(1){
		len = fread(message_buf,sizeof(char),1024,r_fd);
		fwrite(message_buf,sizeof(char),len,w_fd);
		if(len < 1024)
			break;
	}
	//把写入的数据读取出来
	fseek(w_fd,0,SEEK_SET);
	while(1){
		len = fread(message_buf,sizeof(char),1023,w_fd);
		message_buf[len] = 0;
		fprintf(stdout,"%s\n",message_buf);
		if(len < 1023)
			break;
	}
	fclose(r_fd);
	fclose(w_fd);
	return 0;
}
