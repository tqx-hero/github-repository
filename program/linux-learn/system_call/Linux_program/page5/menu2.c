#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
char* menu[] ={
	"a - add new record",
	"d - delete a record",
	"q - quit",
	NULL
};
//选择界面
int getChose(char* info,char** menu){
	int selected,chosed;
	//加载界面
	char** ops = menu;
	while(*ops)
		printf("%s\n",*ops++);
	printf("%s\n",info);
	selected = getchar();
	while(getchar() != '\n');//读取剩余字符直到读到\n
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
		printf("输入有误，请重新选择!\n");
		return getChose(info,menu);
	}
	return selected;
}

int main(){
	int chose;
	//判断标准输出的fd是否连接到终端
	if(!isatty(fileno(stdout))){
		fprintf(stderr,"标准输出已重定向!\n");
		return -1;
	}
	do{
		chose = getChose("请选择对菜单的操作:",menu);
		printf("你选择的操作是: %c\n",chose);
	}while(chose != 'q');
	return 0;
}
