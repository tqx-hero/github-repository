#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//信号驱动程序sigsuspend(3)
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
    sigprocmask(SIG_BLOCK,&set,NULL);
    while(1){
        for(i = 0; i < 5;++i){
            fprintf(stdout,"*");
            fflush(stdout);
            sleep(1);
        }
        fprintf(stdout,"\n");
//        sigprocmask(SIG_UNBLOCK,&set,NULL);
        //使用pause()会出现信号丢失的问题
//        pause();
        sigsuspend(&oset);
    }
    sigprocmask(SIG_SETMASK,&oset,NULL);

    exit(0);
}
