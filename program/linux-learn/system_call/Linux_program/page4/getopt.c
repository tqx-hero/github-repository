#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//getopt函数解析选项与参数
int main(int argc,char** argv){
	int opt;
	while((opt = getopt(argc,argv,":if:lr")) != -1){
		switch(opt){
			case 'i':
			case 'l':
			case 'r':
				printf("option = %c\n",opt);
				break;
			case 'f':
				printf("argumet = %s\n",optarg);
				break;
			case '?':
				printf("invalid option = %c\n",optopt);
				break;
			default :
				printf("option need argument.\n");
				break;
		}
	}
	return 0;
}
