#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
//getopt_long函数解析选项与参数
int main(int argc,char** argv){
	int opt;
	struct option tion[]={
		{"initialize",no_argument,NULL,'i'},
		{"list",no_argument,NULL,'l'},
		{"file",required_argument,NULL,'f'},
		{"restart",0,NULL,'r'},
		{0,0,0,0}
	};
	
	while((opt = getopt_long(argc,argv,":if:lr",tion,NULL)) != -1){
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
