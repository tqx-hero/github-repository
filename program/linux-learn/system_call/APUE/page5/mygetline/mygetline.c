#include "mygetline.h"
//获取文件流一行内容，返回字节数
ssize_t mygetline(char **lineptr,size_t *size,FILE *stream){
	size_t str_len = 0;
	void *newp;
    if(*size < DEFAULT_SIZE)
	*size = DEFAULT_SIZE; 
    if(!*lineptr)
	*lineptr = malloc(*size);
	if(!*lineptr)
	    return -1;
    //读取一行
    while(1){
	    if(!fgets(*lineptr + str_len,*size,stream)){
		    if(feof(stream)){
			    clearerr(stream);
			    return 0;
		    }
		    return -1;
	    }
	    //判断字符串的最后一个字节是否是 \n,如果是则返回
	    str_len = strlen(*lineptr);
	    if(str_len < *size - 1 || (*lineptr)[str_len - 1]  == '\n')
		    break;
	    //如果读到的字节数等于size - 1，并且还没读完一整行，说明这一整行很长，需要重新申请空间，再读
	    newp = realloc(*lineptr,*size * RESIZE_FACTOR);
	    if(!newp)
		    return -1;
	    *size *= RESIZE_FACTOR;
	    *lineptr = (char*)newp;
    }
    return str_len;
}

#define GETLINE_BUFSZ 120

//判断字符是否存在\n
int contain_enter(const char *buf,const ssize_t len,ssize_t *actlen){
	ssize_t i;
	for(i = 0;i < len && buf[i] != '\n';++i);
	if(i >= len){ //到头了，说明不存在\n
		*actlen = i;
		return 0;
	}
	*actlen = i + 1;
	//存在，则设置真实的长度
	return 1;
}

//根据fd获取一行
ssize_t fmygetline(int fd,char **lineptr,size_t *size){
	size_t str_len = 0;
	void *newp;
	char r_buf[GETLINE_BUFSZ];
	ssize_t rbytes,actlen;
	int is_end;
    if(*size < DEFAULT_SIZE)
	*size = DEFAULT_SIZE; 
    if(!*lineptr)
	*lineptr = malloc(*size);
	if(!*lineptr)
	    return -1;
    //读取一行
    while(1){
	    if((rbytes = read(fd,r_buf,sizeof(r_buf))) < 0)
		    return -1;
	    if(rbytes == 0)
		    break;
	    //判断读出的内容是否存在\n
	    is_end = contain_enter(r_buf,rbytes,&actlen);
	    memcpy(*lineptr + str_len,r_buf,actlen);
	    str_len += actlen;
	    if(is_end){
		    //存在\n,需要把最后那个字节填充0，并且把描述符读多的偏移量减回去
		    (*lineptr)[str_len] = 0;
		    lseek(fd,actlen - rbytes,SEEK_CUR);
		    break;
	    }
	    //没有\n，容量不足则需要扩充内存，继续读
	    if(*size - str_len <= sizeof(r_buf)){
	    	newp = realloc(*lineptr,*size * RESIZE_FACTOR);
	    	if(!newp)
			    return -1;
		    *size *= RESIZE_FACTOR;
		    *lineptr = (char*)newp;
	    }
    }
    return str_len;
}

int mygetline_free(char *lineptr){
	free(lineptr);
	return 0;
}
