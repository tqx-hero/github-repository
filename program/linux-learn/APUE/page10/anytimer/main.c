#include <stdio.h>
#include <stdlib.h>
#include "anytimer.h"

static void f1(void * ptr);
static void f2(void * ptr);
int main(){
    puts("Begin!");
    if(mysettimer(5,f1,"aaa") == NULL)
    {
        perror("mysettimer()");
        exit(1);
    }
    if(mysettimer(2,f2,"bbb") == NULL)
    {
        perror("mysettimer()");
        exit(1);
    }
    if(mysettimer(7,f1,"ccc") == NULL)
    {
        perror("mysettimer()");
        exit(1);
    }
    puts("End!");

    while(1)
    {
        write(1,".",1);
        sleep(1);
    }

    exit(0);
}

static void f1(void * ptr){
    fprintf(stdout,"%s",ptr);
    fflush(stdout);
}

static void f2(void * ptr){
    fprintf(stdout,"%s",ptr);
    fflush(stdout);
}
