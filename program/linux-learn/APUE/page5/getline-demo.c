#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    FILE *fdp;
    char *lineptr = NULL;
    size_t linesz = 0;
    fdp = fopen("./dst","r");
    if(!fdp){
	perror("open file error");
	exit(EXIT_FAILURE);
    }

    while(1){
	if(getline(&lineptr,&linesz,fdp) <= 0)
	    break;
	fprintf(stdout,"%lu \n",strlen(lineptr));
	fprintf(stdout,"%lu \n",linesz);
    }
    free(lineptr);
    fclose(fdp);
	return 0;
}
