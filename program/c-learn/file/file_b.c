#include <stdio.h>
#include <string.h>

int main(){
	FILE* fp;
	const char * file_path ="./testfile_b.txt";
	if(!(fp = fopen(file_path,"wb+"))){
		perror("open file error");
		return -1;
	}
	char message[128]="hello world123";
	sprintf(message+strlen(message),"%d",999);
	int w_len = fwrite(message,sizeof(char),strlen(message),fp);
	printf("写入二进制文件长度=%d\n",w_len);
	char recv_buf[128];
	fseek(fp,0,SEEK_SET);
	int r_len = fread(recv_buf,sizeof(char),sizeof(recv_buf),fp);
	printf("读取的文件长度=%d\n",r_len);
	recv_buf[r_len]=0;
	printf("info = %s\n",recv_buf);
	//使用feof函数判断文件是否读取完成了
	//文件读完：返回非0数表示true
	//文件没读完，返回0
	//文本文件因为没有-1，所以可以用ch == EOF来判断是否读取结束
	//但是二进制文件由于字符char类型可以存在-1，就不能使用ch == EOF来判断。
	//所以为了保险起见，建议都使用feof来判断文件是否读取完成
	if(feof(fp))
		printf("文件到末尾了\n");
	return 0;
}
