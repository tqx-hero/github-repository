#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define NUMBER 8000000L
long nums[NUMBER];

static int compared(const void * v1,const void *v2)
{
    return *(long*) v1 >= *(long *) v2;
}

int main(){
    long i;
    //设置随机数
    srandom(time(NULL));
    for(i = 0 ;i < NUMBER;++i)
        nums[i] = random();
    
    qsort(nums,NUMBER,sizeof(long),compared);

    fprintf(stdout,"排序完成，正在汇总:\n");
    for(i = 0;i < NUMBER;++i)
        fprintf(stdout,"%ld\n",nums[i]);

    exit(0);
}
