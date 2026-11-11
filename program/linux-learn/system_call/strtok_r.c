#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char *saveptr,*token;

    char str_buf[] = "ankjfkfd,ba,, \tcddsa\n nnjaa";
    char *str = str_buf;
    while(1){
        token = strtok_r(str," \t\n",&saveptr);
        if(!token)
            break;
        fprintf(stdout,"%s\n",token);
        str = NULL;
    }
    exit(0);
}
