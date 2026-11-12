#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
// system(3)的用法，等价于:fork(2) + exec(3) + wait(2)
int main(int argc,char **argv){
    int status;
    if(argc < 2){
        fprintf(stdout,"Usage main(): invalid argument <argv[1]>! \n");
        exit(1);
    }
    status = system(argv[1]);
    if(WIFEXITED(status))
        fprintf(stdout,"nornal exit ,code = %d\n",WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        fprintf(stdout,"intr by signal ,num = %d\n",WTERMSIG(status));
    return 0;
}
