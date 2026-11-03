#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include "mygetline/mygetline.h"
#define BUFSIZE BUFSIZ
//删除文件的第10行数据,使用系统调用函数
off_t get_offset(int fd,int linenum);

int main(int argc,char **argv){
	int r_fd,w_fd;
	off_t r_off,w_off;
	char *buf = NULL;
	size_t rlen,wlen,pos;
	//检验参数数量
	if(argc < 2){
		fprintf(stderr,"Usage main() : param <argv[1]> must not be empty!\n");
		exit(EXIT_FAILURE);
	}

	//判断文件是否存在
	r_fd = open(argv[1],O_RDWR);
	if(r_fd < 0){
		perror("open file error");
		exit(EXIT_FAILURE);
	}

	//判断文件是否存在第十行,文件没有十行，不需要后续操作，直接返回
	w_off = get_offset(r_fd,9);
	if(w_off < 0)
		goto success_ret;
	
	//移动到第十一行，如果没有第十一行，直接截断文件到第九行末尾
	r_off = get_offset(r_fd,1);
	if(r_off < 0){
		ftruncate(r_fd,w_off);
		goto success_ret;
	}

	//避免栈空间不足，在堆上申请缓冲区空间
	buf = malloc(BUFSIZE);
	if(!buf){
		perror("malloc error");
		goto fail_ret;
	}

	//以读写方式打开文件流，准备在该文件流进行写入
	w_fd = open(argv[1],O_RDWR);
	if(w_fd < 0){
		perror("open wfd error");
		goto fail_ret;
	}

	//设置写指针到第10行起始位置
	if(lseek(w_fd,w_off,SEEK_SET) < 0){
		perror("seek() error");
		goto fail_ret;
	}

	//读取第十一行往后的内容到缓冲区，写入文件，这一步需要循环操作直到文件结束
	pos = 0;
	while(1){
		//从读文件流读取数据到buf，上面已经将读指针读到了第十一行，直接读即可。
		rlen = read(r_fd,buf,BUFSIZE);
		if(rlen == 0)
			break;

		//循环写入缓冲区内的数据,保证读多少，写多少
		while(pos < rlen){
			wlen = write(w_fd,buf + pos,rlen - pos);
			pos += wlen;
		}

		//当读指针到头，循环结束
		if(rlen < BUFSIZE)
			break;
	}

	//重新设置文件大小为写文件流的当前偏移量
	ftruncate(w_fd,lseek(w_fd,0,SEEK_CUR));

success_ret:	
	fprintf(stdout,"file update success!\n");

	//关闭资源
	free(buf);
	if(r_fd)
		close(r_fd);
	if(w_fd)
		close(w_fd);
	return 0;

fail_ret:
	free(buf);
	if(w_fd)
		close(w_fd);
	if(r_fd)
		close(w_fd);
	exit(EXIT_FAILURE);
}

//获取从相对当前位置后linenum行末的字节数(从文件起始位置开始算)
off_t get_offset(int fd,int linenum){
	int cur_linenum = 0;
	char * buf = NULL;
	size_t bytes;
	ssize_t ret;
	off_t nbytes = 0;
	//开始按照行读取
	while(cur_linenum < linenum){
		ret = fmygetline(fd,&buf,&bytes);
		if(ret <= 0){
			free(buf);
			return -1;
		}
		nbytes += ret;
		cur_linenum++;
	}

	//回收内存
	mygetline_free(buf);

	return nbytes;

}
