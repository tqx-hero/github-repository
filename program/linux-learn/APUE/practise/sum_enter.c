#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define EXIT(status)	if(fd >= 0)	\
			  close(fd);	\
			if(buf)		\
			  free(buf);	\
			  exit(status)
#define BUF_SIZE BUFSIZ
//统计换行符个数，也就是文件行数

static int get_char_cnt(const char *buf,const ssize_t buflen,const int findchar);

int main(int argc,char **argv){
	int fd = -1;
	char *buf = NULL;
	ssize_t rlen;
	int char_cnt;
	if(argc < 2){
		fprintf(stderr,"Usage main(): param invalid!\n");
		EXIT(1);
	}

	fd = open(argv[1],O_RDONLY);
	if(fd < 0){
		perror("open() error");
		EXIT(1);
	}
	
	if((buf = malloc(BUF_SIZE)) == NULL){
		perror("malloc() error");
		EXIT(1);
	}

	char_cnt = 0;

	while(1){
		//将数据读取到缓冲区
		rlen = read(fd,buf,BUF_SIZE);
		if(rlen < 0){
			perror("read() error");
			EXIT(1);
		}
		if(rlen == 0)
			break;
		//读出有效数据后，统计缓冲区内数据的字符个数
		char_cnt += get_char_cnt(buf,rlen,'\n');
	}
	fprintf(stdout,"字符 '\\n' 的个数: %d\n",char_cnt);
	EXIT(0);
}

static int get_char_cnt(const char *buf,const ssize_t buflen,const int findchar){
	int cnt,i;
	cnt = 0;
	for(i = 0;i < buflen;++i)
		if((buf[i] & 0xFF) == findchar)
			++cnt;
	return cnt;
}
