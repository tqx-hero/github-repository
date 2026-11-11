#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
//设置进程组的ID
int main(){
    pid_t cid;
    if(fork() == 0){
        //修改子进程自己的组ID
        setpgid(0,0);
        fprintf(stdout,"子进程pgid1 = %llu\n",getpgid(0));
        fprintf(stdout,"子进程pid = %llu\n",getpid());
        sleep(5);
        exit(0);
    }
    if((cid = waitpid(-1,NULL,0)) > 0)
        fprintf(stdout,"子进程ID = %llu\n",cid);
    fprintf(stdout,"pgid1 = %llu\n",getpgid(0));
    fprintf(stdout,"pid = %llu\n",getpid());
    exit(0);
}
