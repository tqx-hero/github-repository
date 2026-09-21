#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){
	struct stat st;
	int flg = fstat(2,&st);
	if(flg == -1){
		perror("");
		return -1;
	}
	printf("size = %ld\n",st.st_size);
	if(S_ISREG(st.st_mode))
		printf("是普通文件\n");
	else if(S_ISDIR(st.st_mode))
		printf("目录\n");
	else if(S_ISBLK(st.st_mode))
		fprintf(stdout,"块设备\n");
	else if(S_ISCHR(st.st_mode))
		fprintf(stdout,"字符设备\n");
	else 
		printf("其他设备\n");
	return 0;
}
