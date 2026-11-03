#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main(){
	int fd = open("./test",O_RDWR | O_TRUNC);
	char buf[]= "nihao1";
	write(fd,buf,sizeof(buf));
	return 0;
}
