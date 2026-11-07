#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <shadow.h>
#include <termios.h>

//加密算法

struct spwd* Getspnam(const char* name){
	struct spwd * spw;
	if(!(spw = getspnam(name))){
		perror("getspnam() error");
		exit(1);
	}
	return spw;
}

char * Getpass(const char*prompt){
	char * pwd;
	if(!(pwd = getpass(prompt))){
		perror("getpass() error");
		exit(1);
	}
	return pwd;
}

char* Crypt(const char* pwd,const char* salt){
	char * ret;
	if(!(ret = crypt(pwd,salt))){
		perror("crypt() error");
		exit(1);
	}
	return ret;
}

int main(int argc,char **argv){
	char *encode,*getpass_info;
	struct spwd *shadow_info;
	struct termios old,news;
	char pwd[512];
	if(argc < 2){
		fprintf(stderr,"需要传入用户名\n");
		exit(1);
	}
	//需要键入密码
	//1、使用getpass(3)
	//getpass_info = Getpass("Please enter your passwd: ");
	
	//2、使用termios选项
	fprintf(stdout,"Please enter your passwd : ");
	fflush(stdout);
	tcgetattr(STDIN_FILENO,&old);
	memcpy(&news,&old,sizeof(news));
	news.c_lflag &= ~ECHO; //关闭回显功能
	news.c_lflag &= ~ECHONL;
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&news);
	fgets(pwd,sizeof(pwd),stdin);
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&old);
	//获取阴影口令上下文
	pwd[strlen(pwd) - 1] = 0;
	fprintf(stdout,"\n");
	fprintf(stdout,"密码是：%s\n",pwd);
	shadow_info = Getspnam(argv[1]);
	encode = Crypt(pwd,shadow_info->sp_pwdp);
	fprintf(stdout,"encode = %s\n",encode);
	fprintf(stdout,"shadow_encode = %s\n",shadow_info->sp_pwdp);
	fprintf(stdout,"match ? %d\n",strcmp(encode,shadow_info->sp_pwdp) == 0);
	return 0;
}
