#include <stdio.h>
extern int add_sum(int x,int y);
void print_msg(int val,char * str){
	printf("%s %d\n",str,val);
	return;
}

int main(){
	int sum= add_sum(100,200);
	printf("from C:result = %d\n",sum);
	return 0;
}
