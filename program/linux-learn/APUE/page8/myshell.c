#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <glob.h>
#define CMD_LINE_SPLIT " \t\n"
#define EXIT_FIAG "exit"
#define LOGOUT_FLAG "logout"
/*******自定义myshell*********/

//自定义命令行的结构体，便于扩展
typedef struct {
    glob_t globres;
} cmd_t ;

/*输出提示符*/
static void prompt(){
    fprintf(stdout,"my-shell01$ ");
    fflush(stdout);
}

//解析输入的字符串，将其转化成argv风格的数组
static void parse_cmd(char *cmdp,cmd_t * cmd){
    char *saveptr,*token;
    char *lineptr = NULL;
    size_t lsz = 0;
    unsigned int i = 0;
    while(1){
        token = strtok_r(cmdp,CMD_LINE_SPLIT,&saveptr);
        if(!token)
            break;
        //解析这个字符串
        if(glob(token,GLOB_NOCHECK | GLOB_APPEND * i ,NULL,&cmd->globres) < 0){
            perror("glob()");
            exit(1);
        }
        i = 1;
        cmdp = NULL;
    }
    return;
}

int main(int argc,char **argv){
    pid_t pid;
    static cmd_t cmd;
    char *lineptr = NULL;
    size_t lsz = 0,exit_len,out_len;
    exit_len = strlen(EXIT_FIAG);
    out_len = strlen(LOGOUT_FLAG);
    while(1){
        /****输入提示符********/
        prompt();
        if(getline(&lineptr,&lsz,stdin) < 0){
            perror("getline() error");
            exit(1);
        }
        //添加退出判断语句
        if(strncasecmp(lineptr,EXIT_FIAG,exit_len) == 0 \
                || strncasecmp(lineptr,LOGOUT_FLAG,out_len) == 0 \
                || strncasecmp(lineptr,"q",1) == 0)
            break;
        /**解析字符串，以空格为分隔符，第一个参数必定是要可执行文件路径**/
        parse_cmd(lineptr,&cmd);
        if(0) //内部命令
        {
        }else //外部命令
        {
            //创建进程
            if((pid = fork()) < 0){
                perror("fork()");
                exit(1);
            }
            if(pid == 0){
                execvp(cmd.globres.gl_pathv[0],cmd.globres.gl_pathv);
                perror("exec()");
                exit(1);
            }
            waitpid(-1,NULL,0);
        }
        globfree(&cmd.globres);
    }
    if(lineptr)
        free(lineptr);
    exit(0);
}


