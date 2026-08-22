#include <stdio.h>
/**
 *
 *
 * sscanf的用法：
 * 将内存中数据按照一定格式拆包
 */
int main(){
	char *buffer="hello world is 20";
	char recv_buf[128],recv_buf2[40];
	int num;
	//%*为跳过某一个区域
	//sscanf(buffer,"%s %s %*s %d",recv_buf,recv_buf2,&num);
	//以下方式读不到正确内容，因为格式不匹配
	//sscanf(buffer,"%s %d",recv_buf,&num);
	//以下方式同样不正确，还是格式不匹配
	//sscanf(buffer,"%s %*s %d",recv_buf,&num);
	sscanf(buffer,"%s %*s %*s %d",recv_buf,&num);
	printf("%s\n",recv_buf);
	//printf("%s\n",recv_buf2);
	printf("%d\n",num);
	return 0;
}
