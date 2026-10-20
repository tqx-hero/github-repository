#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//difftime的用法
int main(){
	time_t t1,t2;
	t1 = time(NULL);
	sleep(2);
	t2 = time(NULL);
	printf("t1 - t2 = %.2g\n",difftime(t1,t2));
	printf("t2 - t1 = %.2g\n",difftime(t2,t1));
	return 0;
}
