#define _GNU_SOURCE
#include <sys/utsname.h>
#include <stdio.h>
//uname()用法
int main(){
	struct utsname name;
	if(uname(&name)){
		perror("uname error");
		return -1;
	}
	printf("sysname = %s,nodename = %s,release = %s,version = %s,hardware = %s,domainname = %s\n",
		name.sysname,name.nodename,name.release,name.version,name.machine,name.domainname);
	return 0;
}
