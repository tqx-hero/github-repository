#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//添加信号屏蔽
static void int_handler(int signum){
   write(1,"int_handler\n",12); 
}

int main(){
    int i;
    sigset_t set,oset;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigprocmask(SIG_UNBLOCK,&set,&oset);
    signal(SIGINT,int_handler);
    while(1){
        for(i = 0; i < 5;++i){
            sigprocmask(SIG_BLOCK,&set,NULL);
            fprintf(stdout,"*");
            fflush(stdout);
            sleep(1);
        }
        fprintf(stdout,"\n");
        sigprocmask(SIG_UNBLOCK,&set,NULL);
    }
    sigprocmask(SIG_SETMASK,&oset,NULL);

    exit(0);
}
