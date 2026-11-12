#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//当前进程直接创建一个会话，正常情况下不会成功
int main(){
    pid_t pid;
    if((pid = fork()) < 0){
        perror("fork()");
        exit(1);
    }
    if(pid == 0){
        fprintf(stdout,"当前进程ID = %llu\n",getpid());
        fprintf(stdout,"当前进程组ID = %llu\n",getsid(0));
        fprintf(stdout,"创建新会话后 SID = %llu\n",setsid());
        fprintf(stdout,"hhhhhhh\n");
     //   exit(0);
        sleep(100);
        exit(0);
    }
    //fprintf(stdout,"退出PID = %llu\n",waitpid(-1,NULL,0));
    pause();
    exit(0);
}
