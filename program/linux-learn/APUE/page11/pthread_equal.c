#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    pthread_t  pt= pthread_self();
    fprintf(stdout,"%d\n",pthread_equal(pt,pt));
    exit(0);
}
