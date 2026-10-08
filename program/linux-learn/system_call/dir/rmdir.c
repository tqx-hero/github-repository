#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//删除文件夹
int main(){
	if(rmdir("./test") == -1){
		exit(-1);
	}
	execlp("ls","ls","-lh",NULL);
	return 0;
}
