#include <stdio.h>
#include <unistd.h>
//popen()以w方式打开管道
int main(){
	FILE* wptr = popen("more","w");
	if(!wptr){
		perror("popen pipe error");
		return -1;
	}
	char buf[]="国庆节快乐，同志们!";
	fwrite(buf,1,sizeof(buf),wptr);
	pclose(wptr);
	return 0;
}
