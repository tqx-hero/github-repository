#include <stdio.h>
#include <string.h>
/*
	拷贝文件DEMO
	通过拷贝字符串形式
*/
int main(){
	const char * src_path= "../test.png",*dst_path = "./cp_test.png";
	//const char * src_path= "../file_b.c",*dst_path = "./cp_file_b_str.txt";
	FILE* r_fp=NULL,*w_fp=NULL;
	if(!(r_fp = fopen(src_path,"rb")) || !(w_fp = fopen(dst_path,"wb")))
		goto close_resource;
	char message_buf[128];
	while(!feof(r_fp)){
		int r_len = fread(message_buf,sizeof(char),sizeof(message_buf),r_fp);
		int w_len = fwrite(message_buf,sizeof(char),r_len,w_fp);
		printf("写入文件len = %d\n",w_len);
	}
close_resource:
	if(r_fp)
		fclose(r_fp);
	if(w_fp)
		fclose(w_fp);
	return 0;
}
