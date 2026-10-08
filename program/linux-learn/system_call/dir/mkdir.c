#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//创建文件夹
int main(){
	if(mkdir("./test",0777) == -1){
		exit(-1);
	}
	execlp("ls","ls","-lh",NULL);
	return 0;
}
