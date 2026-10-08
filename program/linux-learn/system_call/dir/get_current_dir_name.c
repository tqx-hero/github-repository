#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char * pathname = get_current_dir_name();
	printf("当前工作目录 = %s\n",pathname);
	free(pathname);
	return 0;
}
