#include <stdio.h>
#include <string.h>
void reverse_str(char*);
int main(int argc,char** argv,char ** env){
	if(argc == 1){
		printf("必须声明要翻转的字符串\n");
		return -1;
	}
	printf("翻转前：%s\n",argv[1]);
	reverse_str(argv[1]);
	printf("翻转后：%s\n",argv[1]);
	return 0;
}

void reverse_str(char* str){
	int len = strlen(str);
	int left,right;
	for(left = 0,right= len - 1;left < right ;--right,++left){
		char temp = str[left];	
		str[left] = str[right];
		str[right] = temp;
	}
}
