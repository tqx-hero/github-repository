#include <stdio.h>
int add_number(int n1,int n2){
	return n1+n2;	
}

int main(){
	fprintf(stdout,"请输入2个参数值(integer):\n");
	int n1,n2;
	fscanf(stdin,"%d %d",&n1,&n2);
	printf("两数之和 = %d\n",add_number(n1,n2));
	return 0;
}
