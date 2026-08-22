#include <stdio.h>
/**
	sscanf高级用法
*/
int main1(){
	//%s只要遇到\0、\n、空格等会结束匹配
	char *ptr="hello1234",buf[10];
	int num1,num2;
	//%ns 表示需要截取n个字符到相应的内存中
	//%nd 表示需要截取n个字符转换成整型存放到相应的内存中
	//sscanf(ptr,"%5s%2d%2d",buf,&num1,&num2);
	//printf("%s %d %d\n",buf,num1,num2);
	//可以通过*跳过n个字符
	sscanf(ptr,"%5s%*2d%2d",buf,&num1);
	printf("%s %d\n",buf,num1);
	return 0;
}

int main2(){
	//使用正则表达式进行自动匹配
	char buf[]="hgdsdsaodisajDDDSsna129",recv_buf[100];
	int num;
	//通过正则表达式%[a-z](或者使用[a-i]获取a-i区间内的字符)匹配所有字符串
	//如果需要匹配所有大小写字符，写法是：%[A-Za-z]
	//适用于不清楚需要截取多少个字符的情况下
	//sscanf(buf,"%[a-z]%2d",recv_buf,&num);
	//printf("%s %d\n",recv_buf,num);
	//可以与*一起使用，表示屏蔽所有a-z的字符
	sscanf(buf,"%*[a-zA-Z]%d",&num);
	printf("%d\n",num);
	return 0;
}

int main(){
	char *buf ="helloworld#123",recv_buf[100];
	//使用^代表除了后面的这个字符都匹配
	//如：%[^#]代表只要不是#都要
	//%*[^#]代表只要不是#都跳过
	//sscanf(buf,"%[^#]",recv_buf);
	//printf("%s\n",recv_buf);
	//正则表达式：%*[^#] 代表跳过所有不是#的字符
	//后面%*[#]代表跳过#
	//最后%s匹配所有字符放入buf	
	//sscanf(buf,"%*[^#]%*[#]%s",recv_buf);
	//或者按照如下方式，直接写#代表匹配上该字符
	//sscanf(buf,"%*[^#]#%s",recv_buf);
	//或者使用%*c来跳过一个字符
	sscanf(buf,"%*[^#]%*c%s",recv_buf);
	printf("%s\n",recv_buf);
	return 0;
}
