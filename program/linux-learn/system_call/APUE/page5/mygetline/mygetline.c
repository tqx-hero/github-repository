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

int mygetline_free(char *lineptr){
	free(lineptr);
	return 0;
}
