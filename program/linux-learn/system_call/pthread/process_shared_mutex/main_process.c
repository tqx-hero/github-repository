#include "shared.h"
#include <sys/wait.h>
int exit_process;
//创建共享内存，设置多个进程共享锁，打印1000次
void sigchld_handler(int signum){
	pid_t pid;
	while((pid = waitpid(-1,NULL,WNOHANG)) > 0){
		printf("已回收子进程: %d\n",pid);
		exit_process++;
	}
}
//设置共享内存中的结构体,尤其是互斥锁mutex属性为进程间共享
int set_mutex(shared_info_t* sh_info){
	//设置共享变量
	sh_info->total_cnt = PRINT_TOTAL_SIZE;
	sh_info->cur_cnt = 0;
        //获取共享内存存放的结构体
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        //设置进程共享的属性
        if(pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED)){
                fprintf(stderr,"pthread_mutexattr_setpshared error\n");
                exit(-1);
        }
        //加载锁
        pthread_mutex_init(&sh_info->lock,&attr);
        pthread_mutexattr_destroy(&attr);
	return 0;
}

int main(){
	key_t kt = ftok("./",1);
	int shm_id;
	//创建共享内存
	if((shm_id = shmget(kt,sysconf(_SC_PAGE_SIZE),IPC_CREAT | 0666)) == -1){
		perror("shmget error");
		exit(-1);
	}
	//给共享内存设置
	shared_info_t* sh_info = (shared_info_t*)shmat(shm_id,NULL,0);
	if(sh_info == SHMAT_FAIL){
		perror("shmat error");
		goto fail_ret;
	}
	//设置mutex对象
	set_mutex(sh_info);
	//设置信号屏蔽字，先将SIGCHLD放到阻塞集
	sigset_t set,oldset;
	sigemptyset(&set);
	sigaddset(&set,SIGCHLD);
	sigprocmask(SIG_BLOCK,&set,&oldset);
	pid_t pid;
	int i = 0;
	while(i < PRO_COUNT){
		if((pid = fork()) == -1){
			perror("fork error");
			goto fail_ret;
		}
		//子进程开启新的任务
		if(pid == 0){
			//子进程直接恢复屏蔽字
			if(sigprocmask(SIG_SETMASK,&oldset,NULL)){
				perror("child proc sigprocmask error");
				goto fail_ret;
			}
			//子进程执行新的任务
			char proc_name[64],shm_id_s[16];
			sprintf(proc_name,THREAD_PRINT"_%d",getpid());
			sprintf(shm_id_s,"%d",shm_id);
			char * argvs[3] ={proc_name,shm_id_s,NULL};
			execv("./"THREAD_PRINT,argvs);
			perror("execv error");
			goto fail_ret;
		}
		i++;
	}
	//设置信号SIGCHLD处理函数
	struct sigaction sig;
	sig.sa_flags = 0 ;   //不需要开启系统调用重启功能，因为休眠类的函数sleep()不会重启
	sig.sa_handler = sigchld_handler;
	sigemptyset(&sig.sa_mask);
	if(sigaction(SIGCHLD,&sig,NULL)){
		perror("sigaction error");	
		goto fail_ret;
	}
	//将SIGCHLD从阻塞集去除
	sigprocmask(SIG_SETMASK,&oldset,NULL);
	while(exit_process < PRO_COUNT)
		sleep(10);
	//所有进程已退出，开始回收资源
	printf("所有子进程已退出，正在回收资源...\n");
	pthread_mutex_destroy(&sh_info->lock);
	//主进程解绑共享内存
	if(shmdt(sh_info)){
		perror("shmdt error");
		goto fail_ret;
	}
	shmctl(shm_id,IPC_RMID,NULL);
	return 0;
fail_ret:
	exit(-1);
}
