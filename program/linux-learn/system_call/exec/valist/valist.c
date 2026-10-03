#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//递归获取参数列表
void parse_env(char** envp,char* env[]);
int main(){
	char ** envp =(char**) calloc(32,sizeof(char*));
	char * env[] ={"HOME=/home/tqx","PWD=/home/tqx/linux-learn","LOGNAME=tqx",NULL};
	parse_env(envp,env);
	char** cur = envp;
	while(*cur){
		char * temp =*cur;
		fprintf(stdout,"%s\n",temp);
		free(temp);
		cur++;
	}
	free(envp);
	return 0;
}

void parse_env(char** envp,char* env[]){
	if(*env == NULL)
		return;
	char* buf = malloc(strlen(*env)+1);
	strcpy(buf,*env);
	*envp = buf;
	envp++;
	env++;
	parse_env(envp,env);
}

