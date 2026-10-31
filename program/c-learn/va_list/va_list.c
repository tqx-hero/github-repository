#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
//可变参数列表使用
//第一个参数这里定义的是可变参数的个数
void print_valist(int,...);
void print_valist2(int,...);

int main(){
//    print_valist(4,20,30,40,50);
    print_valist2(4,20,30,40,50);
	return 0;
}
//尝试是否可使用memcpy来代替va_copy
void print_valist2(int n,...){
    va_list va,va_bk;
    int tempn = n;
    va_start(va,n);
    memcpy(&va_bk,&va,sizeof(va_list));
    while(n--)
	fprintf(stdout,"int = %u\n",va_arg(va,int));
    va_end(va);
    fprintf(stdout,"----------------------\n");
    while(tempn--)
	fprintf(stdout,"int = %u\n",va_arg(va_bk,int));
    va_end(va_bk);
}

void print_valist(int n,...){
    va_list vc,vc_bk;
    va_start(vc,n);
    va_copy(vc_bk,vc);
    int tempn = n;
    while(n--)
	fprintf(stdout,"int = %u\n",va_arg(vc,int));
    va_end(vc);
    fprintf(stdout,"----------------------\n");
    while(tempn--)
	fprintf(stdout,"int = %u\n",va_arg(vc_bk,int));
    va_end(vc_bk);
}
