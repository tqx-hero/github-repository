#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <glob.h>
#include <time.h>
#define REQUEST_PATH_SIZE 128
#define MODE_BUF_SZ_MIN 16
#define TIME_BUF_SZ_MIN 128

#define MODE_BUF_SIZ 16
#define TIME_BUF_SIZ 128
/*********定义展示哪些字段的宏***************/
#define SHOW_INODE 001
#define SHOW_ALL 002
#define SHOW_LIST 004
#define SHOW_IDS 010

typedef unsigned long int show_flg_t;

//宏函数，用于清空标志位
#define show_flag_clear(flg_name) flg_name = 0L

#define MODE_CASE(type,val)	case type :		\
					ret = val;	\
				break

//实现ls功能，附加选项有-a -l -n -i
// -i :显示inode号码.
// -a:显示所有文件名，包括隐藏文件
// -l:列表形式显示，显示文件所属+组名
// -n：列表形式显示，显示文件属主ID+组ID

//使用getopt(3)解析参数列表

//解析命令行参数
void parse_arguments(int argc,char * const * argv,const char *optstr,\
		                  char **filepath,int *filepath_sizep,show_flg_t *show_flags);
//格式化时间，放入缓冲区
void format_time(char *time_buf,size_t bufsize,time_t t);
//格式化权限字符串，放入缓冲区
void config_mode(char *mode_buf,size_t modesize,mode_t mode);
//打印文件相关的内容
void print_file(int flags,struct stat *st,const char *filepath);

/***********包裹函数***************/
int Lstat(const char *path, struct stat *buf);
struct passwd *Getpwuid(uid_t uid);
struct group *Getgrgid(gid_t gid);
int Chdir(const char *path);
char *Getcwd(char *buf,size_t sz);
int Glob(const char *pattern, int flags,
		                int (*errfunc) (const char *epath, int eerrno),
				                glob_t *pglob);

//实现自定义的功能myls ，可使用的选项：-l -n -i -a 
int main(int argc,char **argv){
	int i;
	char *filepath[REQUEST_PATH_SIZE];
	int filepath_size;
	show_flg_t flags;
	static struct stat st;
	glob_t glb;
	size_t j;
	char *lineptr;
	char *current_dirp;
	if(TIME_BUF_SIZ < TIME_BUF_SZ_MIN){
		fprintf(stderr,"Invalid sizeof(time_buf)! \n");
		exit(1);
	}

	if(MODE_BUF_SIZ < MODE_BUF_SZ_MIN){
		fprintf(stderr,"Invalid sizeof(mode_buf)! \n");
		exit(1);
	}
	//查看当前工作目录
	current_dirp = Getcwd(NULL,0);

	show_flag_clear(flags);
	parse_arguments(argc,argv,"-lina",filepath,&filepath_size,&flags);

	//开始遍历文件路径的数组，逐个调用lstat(2)函数，获取它们的属性
	for(i = 0;i < filepath_size;++i){
		Lstat(filepath[i],&st);

		fprintf(stdout,"%s: \n",filepath[i]);

		//如果是目录，打开目录获取下方值
		if(S_ISDIR(st.st_mode)){
			//改变工作目录到当前
			Chdir(filepath[i]);
			Glob("*",0,NULL,&glb);
			//如果需要的是所有文件，那就获取添加隐藏文件
			if(flags & SHOW_ALL)
				Glob(".*",GLOB_APPEND,NULL,&glb);
			//遍历所有文件名，获取它们的属性
			for(j = 0;j < glb.gl_pathc;++j){
				Lstat(glb.gl_pathv[j],&st);
				print_file(flags,&st,glb.gl_pathv[j]);
			}
			globfree(&glb);

			//恢复工作目录
			Chdir(current_dirp);
		}
		else{
			//如果是文件，直接调用下方
			//按照 /截取文件名用于输出
			lineptr = strrchr(filepath[i],'/');
			if(lineptr)
				print_file(flags,&st,lineptr + 1);
			else
				print_file(flags,&st,filepath[i]);
		}
		fprintf(stdout,"\n");
	}
	fprintf(stdout,"\n");
	exit(0);
}

int Chdir(const char *path){
	int ret;
	if((ret = chdir(path)) < 0){
		perror("chdir() error");
		exit(1);
	} 
	return ret;
}

char *Getcwd(char *buf,size_t sz){
	char *ptr;
	if(!(ptr = getcwd(buf,sz))){
		perror("getcwd() error");
		exit(1);
	}
	return ptr;
}

int Glob(const char *pattern, int flags,
		                int (*errfunc) (const char *epath, int eerrno),
			                glob_t *pglob){
	int ret;
	if(ret = glob(pattern,flags,errfunc,pglob))
		perror("glob() error");
	return ret;
}

void print_file(int flags,struct stat *st,const char *filepath){
	struct passwd *pwd;
	struct group *grp;
	char time_buf[TIME_BUF_SIZ];
	char mode_buf[MODE_BUF_SIZ];
	//拼接属性值
	//1、是否获取INODE
	if(flags & SHOW_INODE)
		fprintf(stdout,"%8lu ",st->st_ino);
	if(flags & SHOW_LIST){
		//2、拼接权限
		memset(mode_buf,0,sizeof(mode_buf));
		config_mode(mode_buf,sizeof(mode_buf),st->st_mode);
		fprintf(stdout,"%s ",mode_buf);

		//展示链接数
		fprintf(stdout,"%2lu ",st->st_nlink);

		//有n选项就显示用户ID与组ID，否则显示用户名与组名
		if(flags & SHOW_IDS)
			fprintf(stdout,"%4lu %4lu ",st->st_uid,st->st_gid);
		else{  //显示用户名与组名
			pwd = Getpwuid(st->st_uid);
			grp = Getgrgid(st->st_gid);
			fprintf(stdout,"%s %s ",pwd->pw_name,grp->gr_name);
		}

		//写入大小
		fprintf(stdout,"%5lu ",st->st_size);

		//写入时间：这里是最后一次修改时间，以 月份 日 时:分形式
		format_time(time_buf,sizeof(time_buf),st->st_mtime);
		fprintf(stdout,"%s ",time_buf);
		//最后加入文件名，并添加换行
		fprintf(stdout,"%s\n",filepath);
	}else
		//最后加入文件名，并添加换行
		fprintf(stdout,"%s ",filepath);
}

struct tm *Localtime(const time_t *timep){
	struct tm *tim;
	if((tim = localtime(timep)) == NULL){
		perror("localtime() error");
		exit(1);
	}
	return tim;
}

size_t Strftime(char *s, size_t max, const char *fmt,const struct tm *tm){
	size_t sz;
	if((sz = strftime(s,max,fmt,tm)) == 0){
		perror("strftime() error");
		exit(1);
	}
	return sz;
}
//辨别文件类型
int config_file_type(mode_t mode){
	int ret;
	switch(mode & S_IFMT){
		MODE_CASE(S_IFREG,'-');
		MODE_CASE(S_IFDIR,'d');
		MODE_CASE(S_IFCHR,'c');
		MODE_CASE(S_IFBLK,'b');
		MODE_CASE(S_IFIFO,'p');
		MODE_CASE(S_IFSOCK,'s');
		MODE_CASE(S_IFLNK,'l');
		default :
			fprintf(stderr,"参数出错，进程退出!\n");
			_exit(1);
		break;
	}
	return ret;
}

#define MODE_PERMISSION(type,val1,val2,index)	if(mode & (type)) 	\
						 mode_buf[index] = val1;\
						else			\
						 mode_buf[index] = val2

#define MODE_PERMISSION_SID(type1,type2,val1,val2,val3,index)  if((mode & (type1)) == 0)\
							mode_buf[index] =  val3;	\
						   else if(mode & (type2))		\
							mode_buf[index] = val2;		\
						   else 				\
							mode_buf[index] = val1
void config_mode(char *mode_buf,size_t modesize,mode_t mode){
	mode_buf[0] = config_file_type(mode);
	//当前用户权限
	MODE_PERMISSION(S_IRUSR,'r','-',1);
	MODE_PERMISSION(S_IWUSR,'w','-',2);
	MODE_PERMISSION_SID(S_IXUSR,S_ISUID,'x','s','-',3);

	//组
	MODE_PERMISSION(S_IRGRP,'r','-',4);
	MODE_PERMISSION(S_IWGRP,'w','-',5);
	MODE_PERMISSION_SID(S_IXGRP,S_ISGID,'x','s','-',6);	

	//其他
	MODE_PERMISSION(S_IROTH,'r','-',7);
	MODE_PERMISSION(S_IWOTH,'w','-',8);
	MODE_PERMISSION(S_IXOTH,'x','-',9);	
	
	//粘着位
	MODE_PERMISSION(S_ISVTX,'t',mode_buf[9],9);
	mode_buf[10] = '.';
}

void format_time(char *time_buf,size_t bufsize,time_t t){
	struct tm *tmp;
	tmp = Localtime(&t);
	Strftime(time_buf,bufsize,"%b %e %H:%M",tmp);
}

struct group *Getgrgid(gid_t gid){
	struct group* grp;
	if(!(grp = getgrgid(gid))){
		perror("getgrgid() error");
		exit(1);
	}
	return grp;
}

struct passwd *Getpwuid(uid_t uid){
	struct passwd *pwd;
	if(!(pwd = getpwuid(uid))){
		perror("getpwuid() error");
		exit(1);
	}
	return pwd;
}

int Lstat(const char *path, struct stat *buf){
	int ret;
	if((ret = lstat(path,buf)) < 0){
		perror("lstat() error");
		exit(1);
	}
	return ret;
}

void parse_arguments(int argc,char * const * argv,const char *optstr,\
		char **filepath,int *filepath_sizep,show_flg_t *show_flags){
	int size = 0;
	int optval;
	while((optval = getopt(argc,argv,optstr)) > 0){
		switch(optval){
			case 'l':
				*show_flags |= SHOW_LIST;
				break;
			case 'i':
				*show_flags |= SHOW_INODE;
				break;
			case 'n':
				*show_flags |= SHOW_IDS | SHOW_LIST;
				break;
			case 'a':
				*show_flags |= SHOW_ALL;
				break;
			case 1 : //文件名，将其放入数组
				filepath[size++] = argv[optind - 1];
				break;
			default :
				fprintf(stderr,"occur error..\n");
				_exit(1);
				break;
		}
	}
	//如果没有声明查询的文件名，将当前目录写入
	if(!size)
		filepath[size++] = ".";
	*filepath_sizep = size;
	return;
}
