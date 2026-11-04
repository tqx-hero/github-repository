#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <unistd.h>
//实现ls -l *.c ../*.c的功能
void print_glob(const glob_t *glb,const size_t gl_off);

int main(int argc,char **argv)
{
	int ret;
	glob_t glb;
	glb.gl_offs = 2;
	if((ret = glob("*.c",GLOB_DOOFFS,NULL,&glb))){
		fprintf(stderr,"glob1() error\n");
		exit(1);
	}
	
	//打印文件列表
	print_glob(&glb,2);

	fprintf(stdout,"............................\n");

	if((ret = glob("../*.c",GLOB_DOOFFS | GLOB_APPEND,NULL,&glb))){
		if(ret != GLOB_NOMATCH){
			fprintf(stderr,"glob2() error\n");
			exit(1);
		}
	}

	print_glob(&glb,2);
	
	//如果没有下方的exec执行，需要释放堆内存
	//globfree(&glb);

	glb.gl_pathv[0] = "ls";
	glb.gl_pathv[1] = "-l";

	//执行ls
	execvp("ls",glb.gl_pathv);
	perror("exec() error");
	exit(1);
}

void print_glob(const glob_t *glb,const size_t gl_off){
	char ** globv;
	size_t cnt,i;
	if(!glb)
		return;
	globv = glb->gl_pathv;
	cnt = glb->gl_pathc;
	for(i = 0;i < cnt;++i)
		fprintf(stdout,"%s\n",globv[gl_off + i]);
	return;
}
