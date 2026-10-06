#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
//使用ls
int main(){
	pid_t pid;
	if((pid = fork()) == -1){
		perror("fork error");
		exit(-1);
	}
	if(pid){
		waitpid(-1,NULL,0);
		return 0;
	}
	int fd = open("./a.txt",O_CREAT | O_WRONLY | O_TRUNC,0644);
	if(fd == -1){
		perror("open a.out error");
		exit(-1);
	}
	dup2(fd,STDOUT_FILENO);
	close(fd);
	char * argv[] = {"ls","-lh",NULL};
	execvp("ls",argv);
	perror("execvp error");
	exit(-1);
}
