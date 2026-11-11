#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
//获取进程组的ID
int main(){
    pid_t pid,cid;
    pid = getpgrp();
    if(fork() == 0){
        fprintf(stdout,"子进程pgid = %llu\n",pid);
        fprintf(stdout,"子进程pgid1 = %llu\n",getpgid(0));
        fprintf(stdout,"子进程pid = %llu\n",getpid());
        exit(0);
    }
    if((cid = waitpid(-1,NULL,0)) > 0)
        fprintf(stdout,"子进程ID = %llu\n",cid);
    fprintf(stdout,"pgid = %llu\n",pid);
    fprintf(stdout,"pgid1 = %llu\n",getpgid(0));
    fprintf(stdout,"pid = %llu\n",getpid());
    exit(0);
}
