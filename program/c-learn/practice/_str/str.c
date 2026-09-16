#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc,char** argv,char** env){
	if(argc ==1){
		fprintf(stderr,"请输入字符串\n");
		exit(-1);
	}
	int i;
	for(i=1;i< argc;++i)
		fprintf(stdout,"%s\n",argv[i]);
	return 0;
}
