#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define LEFT_NUM 3000000
#define RIGHT_NUM 3000200
#define NUM_SIZ (RIGHT_NUM - LEFT_NUM + 1)

//多线程筛选范围内的质数

struct th_arg_t{
    int num;
};

static void* th_handler(void *arg)
{
    int num = ((struct th_arg_t*)arg)->num,i;
    for(i = 2;i <= (num / 2) && (num % i);++i);
    if(i > (num / 2))
        fprintf(stdout,"%d is current num !\n",num);
    pthread_exit(arg);
}

int main(){
    pthread_t pth_arr[NUM_SIZ];
    int i,err;
    struct th_arg_t *thp;
    for(i = LEFT_NUM;i <= RIGHT_NUM ;++i)
    {
        if((thp = malloc(sizeof(struct th_arg_t))) == NULL)
        {
            perror("malloc()");
        }
        thp->num = i;

        if(( err  = pthread_create(pth_arr + i - LEFT_NUM,NULL,th_handler,thp)))
        {
            fprintf(stderr,"%s\n",strerror(err));
            exit(1);
        }
    }

    //回收资源
    for(i = 0;i < NUM_SIZ;++i)
    {
        if((err = pthread_join(pth_arr[i],(void**)&thp)))
        {
            fprintf(stderr,"%s\n",strerror(err));
            exit(1);
        }
        free(thp);
    }

    exit(0);
}
