#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <syslog.h>
#define RETARGET_FILE_NAME "/tmp/deamon-out"

//创建守护进程,该守护进程可以被SIGINT/SIGTERM/SIGQUIT中断退出
static void mydeamon(void);
static void uninstall(void);

static FILE *fdp;
int main(){
    int i;
    mydeamon();
    atexit(uninstall);
    if((fdp = fopen(RETARGET_FILE_NAME,"w")) == NULL){
        syslog(LOG_ERR | LOG_USER,"fopen error : %m");
        exit(1);
    }

    for(i = 0; i < 100 ;++i){
        fprintf(fdp,"%d\n",i);
        fflush(fdp);
        usleep(100 * 1000);
    }

    while(1)
        pause();
}

static void sig_handler(int signum){
    exit(0);
}

static void uninstall(void){
    fclose(fdp);
    write(1,"quit\n",5);
}

static void mydeamon(void){
    pid_t pid;
    int fd;
    umask(0);//设置文件掩码

    if((pid = fork()) < 0){
        perror("fork()");
        exit(1);
    }else if(pid > 0) //父进程退出
        exit(0);

    //子进程创建新会话
    if(setsid() == ((pid_t) -1)){
        perror("setsid()");
        exit(1);
    }

    //设置信号处理函数
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask,SIGINT);
    sigaddset(&sa.sa_mask,SIGTERM);
    sigaddset(&sa.sa_mask,SIGQUIT);

    if(sigaction(SIGINT,&sa,NULL) < 0){
        perror("sigaction()");
        exit(1);
    }
    
    if(sigaction(SIGQUIT,&sa,NULL) < 0){
        perror("sigaction()");
        exit(1);
    }

    if(sigaction(SIGTERM,&sa,NULL) < 0){
        perror("sigaction()");
        exit(1);
    }

    //再次创建子进程，使其不再成为会话的首领
    if((pid = fork()) < 0){
        perror("fork()");
        exit(1);
    }else if(pid > 0)
        exit(0);

    if(chdir("/") < 0){//改变工作目录到根目录
        perror("chdir()");
        exit(1);
    }

    //重定向文件描述符0、1、2
    fd = open("/dev/null",O_RDWR);
    if(fd < 0){
        perror("open()");
        exit(1);
    }

    dup2(fd,STDIN_FILENO);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);
    if(fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
        close(fd);
    return;
} 
