#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//加密算法
int main(){
	char *encode;
	encode = crypt("root","$5$mtQ.pgLITDvXOCf9$");
	if(!encode)
		perror("crypt() error");
	else
		fprintf(stdout,"encode = %s\n",encode);
	fprintf(stdout,"match ? %d\n",strcmp(encode,"$9x9pmlcJgEW2z70XHHeWllb7P2l5T0Tx.Ksxb0UKk84"));
	return 0;
}
