#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void squeeze_dup(char*);
int main(int argc,char ** argv,char** env){
	if(argc ==1){
		printf("param count error\n");
		return EXIT_FAILURE;
	}
	printf("删除前字符串：%s\n",argv[1]);
	squeeze_dup(argv[1]);
	printf("删除后字符串：%s\n",argv[1]);
	return 0;
}

void squeeze_dup(char *s){
	int left=1,len = strlen(s),right =1;
	for(;right < len;++right){
		if(s[right] !=s[left-1])
			s[left++] = s[right];
	}
	s[left] =0;
}
