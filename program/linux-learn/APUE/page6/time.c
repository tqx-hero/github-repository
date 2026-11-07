#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
//使用时间
//

time_t Time(time_t* tm){
	time_t ctime;
	if((ctime = time(tm)) == (time_t) (-1))
	{
		perror("time() error");
		exit(1);
	}
	return ctime;
}

struct tm *Localtime(const time_t *tmp){
	struct tm *temp;
	if(!(temp = localtime(tmp))){
		perror("localtime() error");
		exit(1);
	}
	return temp;
}

size_t Strftime(char *s, size_t max, const char *format,const struct tm *tm){
	size_t ret;
	if(!(ret = strftime(s,max,format,tm))){
		fprintf(stderr,"strftime() error!\n");
		exit(1);
	}
	return ret;
}

int main(){
	time_t tm;
	struct tm * tmp;
	char timebuf[128];
	tm = Time(NULL);
	tmp = Localtime(&tm);
	Strftime(timebuf,sizeof(timebuf),"%Y-%m-%d %H:%M:%S",tmp);
	fprintf(stdout,"当前时间是 : %s\n",timebuf);
	return 0;
}
