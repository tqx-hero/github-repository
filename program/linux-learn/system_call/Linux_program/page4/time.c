#include <time.h>
#include <stdio.h>
//time()的用法
int main(){
	time_t now;
	now = time(NULL);
	printf("%lu\n",now);
	return 0;
}
