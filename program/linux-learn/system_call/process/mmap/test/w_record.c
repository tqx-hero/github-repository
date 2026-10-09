#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
//使用文件读写、mmap()文件映射2种方式对文件进行操作。
#define STR_SIZE 128
#define RECORD_SIZE 100
#define FILE_PATH "./test.txt"
typedef struct {
	int id;
	char string[STR_SIZE];
} record_t;

int main(){
	int fd,i;
	record_t record;	
	off_t nbytes;
	record_t* rct;
	if((fd = open(FILE_PATH,O_CREAT | O_RDWR,0644)) == -1){
		perror("open error");
		exit(-1);
	}
	//定义记录，以系统调用形式写入文件
	for(i = 0;i < RECORD_SIZE;++i){
		record.id = i;
		sprintf(record.string,"RECORD is %d",i);
		write(fd,&record,sizeof(record));
	}
	//重置读指针
	lseek(fd,0,SEEK_SET);
	//获取文件size
	struct stat st;
	if(fstat(fd,&st) == -1){
		perror("fstat error");
		close(fd);
		exit(-1);
	}
	nbytes = st.st_size;
	printf("文件size = %ld",nbytes);
	//文件映射内存块
	rct = (record_t*) mmap(NULL,nbytes,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	if(rct == MAP_FAILED){
		perror("mmap error");
		exit(-1);
	}
	//根据内存块内容读取数据
	printf("文件内容1: id = %d, string = %s\n",rct[0].id,rct[0].string);
	//修改第一条记录
	rct[1].id = 10086;
	strcpy(rct[1].string,"这是一条修改记录");
	//异步写回文件
	if(msync(rct,2 * sizeof(record_t),MS_ASYNC | MS_INVALIDATE) == -1){
		perror("msync error");
		munmap(rct,nbytes);
		exit(-1);
	}
	fprintf(stdout,"修改后的第一条记录 = id = %d,string = %s\n",rct[1].id,rct[1].string);
	munmap(rct,nbytes);
	return 0;
}
