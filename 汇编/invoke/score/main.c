#include <stdio.h>

typedef struct Student {
	char name[16];
	int score;
}Student;
extern int asm_find_max(Student *arr,int count);
void print_max(char *name,int score){
	printf("最高分：%s -> %d 分\n",name,score);
}

int main(){
	Student stus[] ={
		{"张三",85},
		{"李四",92},
		{"王五",77}
	};
	int max = asm_find_max(stus,3);
	printf("C语言收到：%d 分\n",max);
	return 0;
}
