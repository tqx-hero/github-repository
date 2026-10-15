#include <stdio.h>

int main(int argc,char** argv){
	int arg;
	for(arg =0 ;arg < argc;++arg){
		if(argv[arg][0] == '-')	//以-来判断参数是否为选项
			printf("arg[%d] options: %s\n",arg,argv[arg]);
		else 
			printf("arg[%d] argument : %s\n",arg,argv[arg]);
	}
	return 0;
}
