#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define FILE_NAME "/dev/tty"
char* menu[] ={
	"a - add new record",
	"d - delete a record",
	"q - quit",
	NULL
};
//选择界面
int getChose(char* info,char** menu,FILE* in,FILE* out){
	int selected,chosed;
	//加载界面
	char** ops = menu;
	while(*ops)
		fprintf(out,"%s\n",*ops++);
	fprintf(out,"%s\n",info);
	selected = getc(in);
	while(getc(in) != '\n');//读取剩余字符直到读到\n
	ops = menu;
	chosed = 0;
	while(*ops){
		if(selected == (*ops)[0]){
			chosed =1;
			break;		
		}
		ops++;
	}
	//如果选择的不对，则进行选择
	if(!chosed){
		fprintf(stderr,"输入有误，请重新选择!\n");
		return getChose(info,menu,in,out);
	}
	return selected;
}

int main(){
	int chose;
	FILE *in,*out;
	//判断标准输出的fd是否连接到终端
	if(!isatty(fileno(stdout)))
		fprintf(stderr,"标准输出已重定向!\n");
	//使用打开文件流的方式获取文件输入输出流
	in = fopen(FILE_NAME,"r");
	out = fopen(FILE_NAME,"w");
	do{
		chose = getChose("请选择对菜单的操作:",menu,in,out);
		fprintf(out,"你选择的操作是: %c\n",chose);
	}while(chose != 'q');
	return 0;
}
