#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    puts("begin");

    fflush(NULL);   /***必须注意冲刷缓冲区,exec替换不会主动冲刷***/
    pid = fork();
    if(pid < 0){
        perror("fork() error");
        exit(1);
    }
    if(!pid){
        execl("/bin/sleep","sllll","100",NULL);
        perror("exec() error");
        exit(1);
    }
    waitpid(-1,NULL,0);
    puts("end");
    exit(0);
}
