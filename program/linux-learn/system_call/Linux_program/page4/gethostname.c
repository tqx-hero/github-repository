#include <unistd.h>
#include <stdio.h>
//gethostname(2)的使用
int main(){
	char name[20];
	if(gethostname(name,sizeof(name))){
		perror("gethostname error");
		return -1;
	}
	printf("hostname = %s\n",name);
	return 0;
}
