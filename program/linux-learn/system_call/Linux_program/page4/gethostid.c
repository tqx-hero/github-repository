#include <unistd.h>
#include <stdio.h>
//gethostid(2)
int main(){
	long hostid = gethostid();
	char* idp = (char*) &hostid;
	printf("host ID = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
		idp[7] & 0xFF,idp[6] & 0xFF,idp[5] & 0xFF,idp[4] & 0xFF,idp[3] & 0xFF,idp[2] & 0xFF,idp[1] & 0xFF,idp[0] & 0xFF);
	return 0;
}
