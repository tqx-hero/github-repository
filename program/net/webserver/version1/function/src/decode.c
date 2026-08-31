#include "../header/decode.h"
#include <stdio.h>
unsigned char to_hex_num(char ch){
	if(ch >= '0' && ch <='9')
		return ch - '0';
	if(ch >= 'a' && ch <= 'f')
		return ch - 'a' +10;
	return ch - 'A' +10;
}

int utf_8_decoder(char* dst,const char* src){
	
	for(;src[0] !=0;dst++,src++){
		//转中文条件，必须满足%开头，紧接着后面2个字符分别可以表示成16进制数字
		if(src[0] == '%' && isxdigit(src[1]) && isxdigit(src[2])){
			dst[0] = (to_hex_num(src[1]) << 4) + to_hex_num(src[2]);
			src+=2;
		} else if(src[0] == '+'){
			dst[0] = ' ';
		}
		else{
			dst[0] = src[0];
		}
	
	}
	dst[0] =0;
	return 0;
}
/*

int main(){
	char buf[] = "static/%E8%8B%A6%E7%93%9C.html";
  	char decode_buf[128];
	utf_8_decoder(decode_buf,buf);
	printf("%s\n",decode_buf);
	return 0;
}
*/
