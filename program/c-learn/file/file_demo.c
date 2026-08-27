#include <stdio.h>
#include <string.h>
/*
fopen：
*/
int main(){
	FILE * fp;
	const char* file_path = "./testfile.txt";
	if(!(fp = fopen(file_path,"w+"))){
		perror("open file error");
		return -1;	
	}
	char message[128]="hello world";
	int len = fwrite(message,sizeof(char),strlen(message),fp);
	printf("写入文件的总长度=%d\n",len);
	fseek(fp,0,SEEK_SET);
	char recv_buf[128];
	int r_len = fread(recv_buf,sizeof(char),sizeof(recv_buf),fp);
	recv_buf[r_len] = 0;
	printf("读到的总长度=%d\n",r_len);
	printf("文件内容=%s\n",recv_buf);
	fclose(fp);
	return 0;
}
