#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define PATH_SIZE PATH_MAX
//实现du功能，即获取某个文件/目录所占磁盘的大小，以KB为单位。

static size_t mydu(char *filepath){
	size_t kbytes,subdir_kbytes;
	static struct stat st;
	static struct dirent* dir_ent;
	size_t str_len;
	DIR *dir;
	char *temp_filepath;
	//获取文件属性，并判断是否为目录
	if(lstat(filepath,&st) < 0){
		perror("stat() error");
		exit(1);
	}
	kbytes = 0LL;
	//判断是否为目录
	if(!S_ISDIR(st.st_mode))
		kbytes += st.st_blocks / 2;
	else{
		//获取当前目录的长度
		str_len = strlen(filepath);
		
		//使用strrchr(3)获取当前字符串最后的那个/指针
		//strp = strrchr(filepath,'/');
		//if(strp == NULL)

		//如果它是 . ，即当前目录，直接返回它的所占块数
		if(filepath[str_len - 1] == '.' || filepath[str_len - 2] == '.')
			return st.st_blocks >> 1;

		subdir_kbytes = 0;
		//是目录，打开目录
		dir = opendir(filepath);
		if(dir == NULL){
			perror("opendir() error");
			exit(1);
		}
		
		if((temp_filepath = malloc(str_len + 1)) == NULL){
			perror("malloc tempfile error");
			exit(1);
		}

		//备份文件名
		strcpy(temp_filepath,filepath);

		//格式化目录
		if(filepath[str_len - 1] != '/')
			filepath[str_len++] = '/';

		//递归统计子目录
		while((dir_ent = readdir(dir)) != NULL){
			//抛出自身目录与上级目录，防止递归嵌套
			if(strncmp(dir_ent->d_name,"..",2)){
				sprintf(filepath + str_len,"%s",dir_ent->d_name);
				subdir_kbytes += mydu(filepath);
			}
		}
		//输出子目录的所占磁盘数,并将其添加到最终统计中
		fprintf(stdout,"%ld	%s\n",subdir_kbytes,temp_filepath);
		free(temp_filepath);
		closedir(dir);
		kbytes += subdir_kbytes;
	}
	return kbytes;
}

int main(int argc,char ** argv){
	size_t kbytes;
	struct stat st;
	size_t buf_size;
	char * path_buf;
	int config;
	//参数校验，简单起见必须传参，只解析一个参数
	if(argc < 2){
		fprintf(stderr,"Usage main() : param invalid ! \n");
		exit(1);
	}
	if(lstat(argv[1],&st) < 0){
		perror("main stat() error");
		exit(1);
	}
	//递归解析文件
	buf_size = PATH_SIZE << 1;
	path_buf = malloc(buf_size);
	if(path_buf == NULL){
		perror("malloc() error");
		exit(1);
	}
	//如果路径是.或..，则直接展开成绝对路径
	if(config = (strncmp(argv[1],".",1) == 0 || strncmp(argv[1],"..",2) == 0)){
		//改变工作目录
		if(chdir(argv[1]) < 0){
			perror("chdir() error");
			exit(1);
		}
		
		//获取工作目录的绝对路径
		if(getcwd(path_buf,buf_size) == NULL){
			perror("main() getcwd() error");
			exit(1);
		}
	}else//不是以上两种情况，就复制路径到缓冲区
		strcpy(path_buf,argv[1]);

	kbytes = mydu(path_buf);
	if(!S_ISDIR(st.st_mode))
		fprintf(stdout,"%ld	%s\n",kbytes,argv[1]);

	free(path_buf);
	exit(0);
}
