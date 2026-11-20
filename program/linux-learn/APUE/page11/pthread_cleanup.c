#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//pthread_cleanup_push(3)与pthread_cleanup_pop(3)的用法

static void cleanup(void *arg)
{
    fprintf(stdout,"%s\n",arg);
}

static void *handler(void * arg)
{
    fprintf(stdout,"thread create success !\n");
    pthread_cleanup_push(cleanup,"cleanup : 1");
    pthread_cleanup_push(cleanup,"cleanup : 2");
    puts("push end!");
    pthread_exit(NULL);
    puts("exit fail!");
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
}

int main(){
    pthread_t pd;
    int err;
    puts("Begin!");

    err = pthread_create(&pd,NULL,handler,NULL);
    if(err){
        fprintf(stderr,"%s\n",strerror(err));
        exit(1);
    }

    pthread_join(pd,NULL);
    puts("End!");
    exit(0);
    //    pthread_exit(0);
}
