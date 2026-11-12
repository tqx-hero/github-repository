#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <syslog.h>
#define RETARGET_FILE_NAME "/tmp/deamon-out"
//创建守护进程
//1、fork()子进程，父进程退出
//2、子进程设置文件创建掩码umask，这一步是为了守护进程需要创建文件时所使用
//3、通过setsid(3)创建新的会话,这一项所做的有：创建新会话、自己成为新会话的leader、脱离与之前控制终端的联系
//4、彻底屏蔽SIGHUP信号，方法是使用sigaction将SIGHUP信号设置为忽略处理
//5、fork()子进程，父进程退出，这一步是解决父进程仍然是会话leader的问题，
//如果后面该进程再次打开一个终端，那就可以通过终端对其发送信号，违背了守护进程初衷，再次生成的子进程不是leader
//子进程作为一个孤儿进程组，无法再次获得控制终端，再进行设置。
//6、改变进程工作目录，这样做避免进程挂载到的目录无法卸载。
//7、关闭文件描述符0、1、2.严谨一点的，关闭所有文件描述符表的fd，具体描述符表大小通过sysconf(3)获取
//或者将0、1、2描述符重定向到/dev/null

//创建守护进程
static void mydeamon(void);

int main(){
    FILE *fdp;
    int i;
    mydeamon();

    if((fdp = fopen(RETARGET_FILE_NAME,"w")) == NULL){
        syslog(LOG_ERR | LOG_USER,"fopen error : %m");
        exit(1);
    }

    for(i = 0;i < 10086;++i){
        fprintf(fdp,"%d\n",i);
        fflush(fdp);
        usleep(100 * 1000);
    }

    while(1)
        pause();
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

    //忽略SIGHUP信号
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGHUP,&sa,NULL) < 0){
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
