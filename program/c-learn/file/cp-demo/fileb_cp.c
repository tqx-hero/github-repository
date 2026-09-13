#include <stdio.h>
#include <string.h>
/*
	拷贝文件DEMO
	逐个字符拷贝
*/
int main(){
	const char * src_path= "../file_b.c",*dst_path = "./cp_file_b_char.txt";
	FILE* r_fp=NULL,*w_fp=NULL;
	if(!(r_fp = fopen(src_path,"rb")) || !(w_fp = fopen(dst_path,"wb")))
		goto close_resource;
	char message_buf[128];
	int size=0;
	while(!feof(r_fp)){
		char ch = fgetc(r_fp);
		message_buf[size++] = ch;
		if(size == sizeof(message_buf)){
			int w_len = fwrite(message_buf,sizeof(char),size,w_fp);
			printf("写入文件len = %d\n",w_len);
			size =0;
		}
	}
	if(size)
		fwrite(message_buf,sizeof(char),size,w_fp);
close_resource:
	if(r_fp)
		fclose(r_fp);
	if(w_fp)
		fclose(w_fp);
	return 0;
}
