#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <setjmp.h>
#include <string.h>
//使用时间函数，将当前时间写入日志文件，前1分钟每1s写入一次，之后每五分钟写入一次
//写入四次之后结束
#define CLOSE_RESOURCE 	if(fdp)			\
				fclose(fdp)	
#define TIME_BUF_SIZE 512
jmp_buf jb;

static FILE *Fopen(const char* pathname,char *mode){
	FILE *fdp;
	if((fdp = fopen(pathname,mode)) == NULL){
		perror("fopen() error");
		longjmp(jb,1);
	}
	return fdp;
}

static struct tm *Localtime(const time_t *time){
	struct tm *tmp;
	if(!(tmp = localtime(time))){
		perror("localtime() error");
		longjmp(jb,2);
	}
	return tmp;
}

static size_t Strftime(char *s, size_t max, const char *format,
		                              const struct tm *tm){
	size_t ret;
	if((ret = strftime(s,max,format,tm)) == 0){
		perror("strftime() error");
		longjmp(jb,3);
	}
	return ret;
}

static size_t Fwrite(const void *ptr, size_t size, size_t nmemb,
		                      FILE *stream){
	size_t sz;
	if((sz = fwrite(ptr,size,nmemb,stream)) != size * nmemb){
		perror("fwrite() error");
		longjmp(jb,4);
	}
	return sz;
}

static size_t get_current_tm(char *time_buf,int count,size_t buf_size){
	struct tm* tmp;
	size_t str_len,ret_len;
	time_t cur_time;
	cur_time =time(NULL);
	tmp = Localtime(&cur_time);
	//时间转化成格式化字符串
	str_len = sprintf(time_buf,"%d ",count);
	ret_len= Strftime(time_buf + str_len,buf_size - str_len,"%Y-%m-%d %H:%M:%S",tmp);
	strcat(time_buf,"\n");
	return str_len + ret_len + 1L;
}

int main(int argc,char ** argv){
	FILE *fdp;
	int count,cnt;
	char time_buf[TIME_BUF_SIZE];
	size_t buflen;
	fdp = NULL;
	if(argc < 2){
		fprintf(stderr,"Usage main() error: param invalid!\n");
		goto fail_ret;
	}
	if(!setjmp(jb)){
		fdp = Fopen(argv[1],"w");
		//开始写入时间
		count = 0;
		while(count++ < 60){
			buflen = get_current_tm(time_buf,count,sizeof(time_buf));
			//将buf写入文件
			sleep(1);
			Fwrite(time_buf,sizeof(char),buflen,fdp);
		}
		//1分钟结束以后，开始5分钟写入一次
		cnt = 0;
		while(cnt++ < 3){
			buflen = get_current_tm(time_buf,count++,sizeof(time_buf));
			sleep(5 * 60);
			Fwrite(time_buf,sizeof(char),buflen,fdp);
		}
	}else
		goto fail_ret;	
	fprintf(stdout,"file write success!\n");
	CLOSE_RESOURCE;
	exit(EXIT_SUCCESS);
fail_ret:
	CLOSE_RESOURCE;
	exit(EXIT_FAILURE);
}
