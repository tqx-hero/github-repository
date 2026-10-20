#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "./record.dat"
//mmap内存映射的demo
//先使用fopen..等库函数往文件中添加数据，再使用mmap读取数据

typedef struct {
	int integer;
	char str[128];
} record_t;

int main(){
	//通过fopen等库函数将数据存入文件
	FILE* fp =  fopen(FILE_NAME,"w");
	if(!fp){
		perror("fopen error");
		exit(EXIT_FAILURE);
	}
	record_t records[100];
	int i;
	for(i=0;i<100;++i){
		records[i].integer = i;
		sprintf(records[i].str,"RECORD-%d",i);
	}
	fwrite(records,sizeof(records),1,fp);
	fclose(fp);
	//通过mmap映射文件到内存，进行查询、修改
	int fd;
	record_t * recordp;
	if((fd = open(FILE_NAME,O_RDWR)) == -1){
		perror("open error");
		exit(EXIT_FAILURE);
	}
	recordp = (record_t*) mmap(NULL,sizeof(records),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	//读取第多少43条记录
	printf("第43条记录： integer = %d,str = %s\n",recordp[43].integer,recordp[43].str);
	//修改这条记录的号码为243，同时更新字符串
	recordp[43].integer = 243;
	sprintf(recordp[43].str,"RECORD-%d",243);
	msync(&recordp[43],sizeof(record_t),MS_ASYNC); //只更新这一条记录
	munmap(recordp,sizeof(records));
	//再次读取文件，获取文件内容输出
	if((fd = open(FILE_NAME,O_RDONLY)) == -1){
		perror("open file error");
		exit(-1);
	}
	record_t r_rec;
	int j = 0;
	while(read(fd,&r_rec,sizeof(record_t)) > 0)
		printf("记录[%d]： integer = %d,str = %s\n",j++,r_rec.integer,r_rec.str);
	close(fd);
	return 0;
}
