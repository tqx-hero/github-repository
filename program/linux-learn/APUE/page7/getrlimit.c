#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <setjmp.h>
//getrlimit(3)函数的使用
#define do_get(name) print_limit(#name,name)
sigjmp_buf jb;

void print_limit(char *name,int value);

int main(){
	if(!sigsetjmp(jb,1)){
		do_get(RLIMIT_AS);
		do_get(RLIMIT_CORE);
		do_get(RLIMIT_CPU);
		do_get(RLIMIT_DATA);
		do_get(RLIMIT_FSIZE);
		do_get(RLIMIT_NOFILE);
		do_get(RLIMIT_STACK);
#ifdef	RLIMIT_MSGQUEUE
		do_get(RLIMIT_MSGQUEUE);
#endif

#ifdef	RLIMIT_NICE
		do_get(RLIMIT_NICE);
#endif

#ifdef	RLIMIT_NPROC
		do_get(RLIMIT_NPROC);
#endif

#ifdef	RLIMIT_RSS
		do_get(RLIMIT_RSS);
#endif

#ifdef	RLIMIT_SIGPENDING
		do_get(RLIMIT_SIGPENDING);
#endif

#ifdef	RLIMIT_SWAP
		do_get(RLIMIT_SWAP);
#endif
	}else
		fprintf(stderr,"getrlimit fail.\n");
	return 0;
}

void print_limit(char *name,int value){
	struct rlimit limit;
	if(getrlimit(value,&limit) < 0){
		perror("getrlimit() error");
		siglongjmp(jb,1);
	}
	fprintf(stdout,"%s  ",name);
	if(limit.rlim_cur == RLIM_INFINITY)
		fprintf(stdout,"(unlimited)  ");
	else if(limit.rlim_cur == RLIM_SAVED_CUR)
		fprintf(stdout,"(too big)  ");
	else
		fprintf(stdout,"%lu  ",limit.rlim_cur);

	if(limit.rlim_max == RLIM_INFINITY)
		fprintf(stdout,"(unlimited)  ");
	else if(limit.rlim_max == RLIM_SAVED_MAX)
		fprintf(stdout,"(too big)  ");
	else
		fprintf(stdout,"%lu  ",limit.rlim_max);
	fprintf(stdout,"\n");
	return;
}
