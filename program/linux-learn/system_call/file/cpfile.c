#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUF_SIZE 1024
//拷贝文件argv[1] -> argv[2] 
int main(int argc ,char** argv ,char** env){
	char * buf =NULL;
	int r_fd = -1,w_fd = -1;
	if(argc !=3){
		fprintf(stdout,"请输入要拷贝的文件名称\n");
		exit(-1);
	}
	r_fd = open(argv[1],O_RDONLY);
	if(r_fd ==-1){
		perror("");
		goto fail_ret;
	}
	w_fd = open(argv[2],O_CREAT | O_WRONLY | O_TRUNC,0644);
	if(w_fd ==-1){
		perror("");
		goto fail_ret;
	}
	buf = malloc(BUF_SIZE);
	if(!buf){
		perror("");
		goto fail_ret;
	}
	//开始从a文件读取到b文件
	int r_len;
	while(1){
		r_len = read(r_fd,buf,BUF_SIZE);
		write(w_fd,buf,r_len);
		//当读取到的字符数量小于buf总长，读取结束，退出
		if(r_len < BUF_SIZE)
			break;
	}
	fprintf(stdout,"拷贝结束\n");
	close(r_fd);
	close(w_fd);
	free(buf);	
	return 0;	
fail_ret:
	if(r_fd != -1)
		close(r_fd);
	if(w_fd != -1)
		close(w_fd);
	if(buf)
		free(buf);
	exit(-1);
}
