#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
//使用时间
//

size_t Strftime(char *s, size_t max, const char *format,const struct tm *tm){
	size_t ret;
	if(!(ret = strftime(s,max,format,tm))){
		fprintf(stderr,"strftime() error!\n");
		exit(1);
	}
	return ret;
}

char * Strptime(const char *s, const char *format, struct tm *tm){
	char* ret;
	if(!(ret = strptime(s,format,tm))){
		perror("strptime() errpr");
		exit(1);
	}
	return ret;
}

int main(){
	time_t tm;
	struct tm  tmp;
	char  timebuf[128],ptimebuf[128] = "2026-11-07 14:51:10";
	Strptime(ptimebuf,"%Y-%m-%d %H:%M:%S",&tmp);
	Strftime(timebuf,sizeof(timebuf),"%Y-%m-%d %H:%M:%S",&tmp);
	fprintf(stdout,"当前时间是 : %s\n",timebuf);
	return 0;
}
