#include "mygetline.h"
//测试mygetline()函数
int main(){
	FILE *fdp;
	char *lineptr = NULL;
	size_t linesz = 0;
	ssize_t bytes;
	if((fdp = fopen("./dst","r")) == NULL){
		perror("open file error");
		exit(EXIT_FAILURE);
	}
	
	//按照行读取
	while(1){
		if((bytes = mygetline(&lineptr,&linesz,fdp)) < 0){
			perror("getline error");
			exit(EXIT_FAILURE);
		}
		else if(!bytes)
			break;
		fprintf(stdout,"%s",lineptr);
		fprintf(stdout,"linesz = %lu\n",linesz);
		fprintf(stdout,"strlen = %lu\n",strlen(lineptr));
	}
	mygetline_free(lineptr);
	fclose(fdp);
	return 0;
}
