#include <syslog.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define PRO_NAME "mysyslog"
//syslog()的使用
int main(){
	//1、直接使用syslog(3)
	/*
	if(open("./name12.txt",O_RDONLY)){
		syslog(LOG_ERR | LOG_USER,"open file \"./name12.txt\" error : %m");
		return -1;
	}
	*/

	//2、使用openlog(3)，给日志输出进行适当配置
	/*
	openlog(PRO_NAME,LOG_PID | LOG_CONS,LOG_USER);
	if(open("./name12.txt",O_RDONLY)){
		syslog(LOG_ERR | LOG_USER,"open file \"./name12.txt\" error : %m");
		return -1;
	}
	*/

	//3、设置了日志掩码
	openlog(PRO_NAME,LOG_PID | LOG_CONS,LOG_USER);
	int oldmask = setlogmask(LOG_UPTO(LOG_ERR));
	printf("原掩码 = %d\n",oldmask);
	if(open("./name12.txt",O_RDONLY)){
		syslog(LOG_ERR | LOG_USER,"open file \"./name12.txt\" [level: LOG_ERR] : %m");
		syslog(LOG_WARNING | LOG_USER,"open file \"./name12.txt\" [level: LOG_WARNING] : %m");
		return -1;
	}
	return 0;
}
