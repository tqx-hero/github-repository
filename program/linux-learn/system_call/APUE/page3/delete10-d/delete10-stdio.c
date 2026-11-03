#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#define BUFSIZE BUFSIZ
//删除文件的第10行数据
off_t get_offset(FILE *fdp,int linenum);

int main(int argc,char **argv){
	FILE *r_fdp,*w_fdp;
	off_t r_off,w_off;
	char *buf = NULL;
	size_t rlen,wlen,pos;
	//检验参数数量
	r_fdp = w_fdp = NULL;
	if(argc < 2){
		fprintf(stderr,"Usage main() : param <argv[1]> must not be empty!\n");
		exit(EXIT_FAILURE);
	}

	//判断文件是否存在
	r_fdp = fopen(argv[1],"r+");
	if(r_fdp == NULL){
		perror("open file error");
		exit(EXIT_FAILURE);
	}

	//判断文件是否存在第十行,文件没有十行，不需要后续操作，直接返回
	w_off = get_offset(r_fdp,9);
	if(w_off < 0)
		goto success_ret;
	
	//移动到第十一行，如果没有第十一行，直接截断文件到第九行末尾
	r_off = get_offset(r_fdp,1);
	if(r_off < 0){
		ftruncate(fileno(r_fdp),w_off);
		goto success_ret;
	}

	//避免栈空间不足，在堆上申请缓冲区空间
	buf = malloc(BUFSIZE);
	if(!buf){
		perror("malloc error");
		goto fail_ret;
	}

	//以读写方式打开文件流，准备在该文件流进行写入
	w_fdp = fopen(argv[1],"r+");
	if(!w_fdp){
		perror("open wfd error");
		goto fail_ret;
	}

	//设置写指针到第10行起始位置
	if(fseek(w_fdp,w_off,SEEK_SET) < 0){
		perror("seek() error");
		goto fail_ret;
	}

	//清空读缓冲区，准备后续读入第十一行开始的数据
	//fflush(r_fdp);

	//读取第十一行往后的内容到缓冲区，写入文件，这一步需要循环操作直到文件结束
	pos = 0;
	while(1){
		//从读文件流读取数据到buf，上面已经将读指针读到了第十一行，直接读即可。
		rlen = fread(buf,1,BUFSIZE,r_fdp);
		if(rlen == 0)
			break;

		//循环写入缓冲区内的数据,保证读多少，写多少
		while(pos < rlen){
			wlen = fwrite(buf + pos,1,rlen - pos,w_fdp);
			pos += wlen;
		}

		//当读指针到头，循环结束
		if(feof(r_fdp))
			break;
	}

	//重新设置文件大小为写文件流的当前偏移量
	ftruncate(fileno(w_fdp),ftell(w_fdp));

success_ret:	
	fprintf(stdout,"file update success!\n");

	//关闭资源
	free(buf);
	if(r_fdp)
		fclose(r_fdp);
	if(w_fdp)
		fclose(w_fdp);
	return 0;

fail_ret:
	free(buf);
	if(w_fdp)
		fclose(w_fdp);
	if(r_fdp)
		fclose(w_fdp);
	exit(EXIT_FAILURE);
}

//获取从相对当前位置后linenum行末的字节数(从文件起始位置开始算)
off_t get_offset(FILE *fdp,int linenum){
	int cur_linenum = 0;
	char * buf = NULL;
	size_t bytes;
	ssize_t ret;
	off_t nbytes = 0;
	//开始按照行读取
	while(cur_linenum < linenum){
		ret = getline(&buf,&bytes,fdp);
		if(ret <= 0){
			free(buf);
			return -1;
		}
		nbytes += ret;
		cur_linenum++;
	}

	//回收内存
	free(buf);

	return nbytes;

}
