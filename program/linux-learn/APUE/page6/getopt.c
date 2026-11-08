#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define FMT_BUFSIZ 512
#define TIME_BUF_SIZ 512
#define 	SWITCH_OPT(num,str)	case num : 					 \
						strncat(fmtbuf,str,remain_size);			 \
						remain_size = FMT_BUFSIZ - strlen(fmtbuf);\
					break
//使用命令行参数解析函数getopt(3)
//以解析当前时间为例，根据不同的选项输入，返回选项所代表的时间值
/**
 *	Y：年
 *	m：月
 *	d：日
 *	H：小时
 *	M：分钟
 *	S：秒
 */

FILE *Fopen(const char *name,const char *mode){
	FILE *fdp;
	if(!(fdp = fopen(name,mode))){
		perror("fopen() error");
		exit(1);
	}
	return fdp;
}

int main(int argc,char ** argv){
	//1、getopt(3)函数解析命令选项，生成fmt字符出
	int optval;	
	int fd;
	FILE *fdp;
	char fmtbuf[FMT_BUFSIZ],time_buf[TIME_BUF_SIZ];
	size_t remain_size;
	time_t ctime;
	struct tm *tmp;
	remain_size = FMT_BUFSIZ;
	fdp = NULL;
	while((optval = getopt(argc,argv,"-YmdHMS")) > 0){
		switch(optval){
			SWITCH_OPT('Y',"%Y ");
			SWITCH_OPT('m',"%m ");
			SWITCH_OPT('d',"%d ");
			SWITCH_OPT('H',"%H ");
			SWITCH_OPT('M',"%M ");
			SWITCH_OPT('S',"%S ");
			case 1:
				fdp = Fopen(argv[optind - 1],"w");
				break;
			default:
				break;
		}
	}
	if(fdp){ //如果存在写入的文件，使用dup2(2)将标准输出重定向
		fd = fileno(fdp);
		if(fd != STDOUT_FILENO){
			dup2(fileno(fdp),STDOUT_FILENO);
			fclose(fdp);
		}
	}	
	//2、根据fmt使用strftime(3)解析当前的时间，输出
	ctime = time(NULL);
	tmp = localtime(&ctime);
	strftime(time_buf,sizeof(time_buf),fmtbuf,tmp);
	puts(time_buf);
	exit(0);
}
