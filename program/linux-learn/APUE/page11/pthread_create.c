#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void *handler(void * arg)
{
    fprintf(stdout,"thread create success !\n");
    pthread_exit(NULL);
}

int main(){
    pthread_t pd;
    int err;
    puts("Begin!");
    err = pthread_create(&pd,NULL,handler,NULL);
    if(err){
        fprintf(stderr,"%s\n",strerror(err));
    }
    puts("End!");
    pthread_exit(0);
}
