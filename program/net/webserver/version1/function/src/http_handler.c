#include "../header/http_handler.h"
#include <signal.h>
/**
 * @brief 根据文件名后缀获取HTTP Content‑Type MIME字符串
 * @param filename 文件名，如 index.html、data.json、a.txt
 * @return 静态字符串，不要free；未知后缀返回 application/octet‑stream
 */
const char *get_content_type(const char *filename)
{
	// 找到最后一个 '.' 的位置
	const char *ext = strrchr(filename, '.');
	if (ext == NULL)
	{
		// 没有后缀
		return "application/octet-stream";
	}
	ext++; // 跳过 '.'，指向后缀文本，例如 "html"

	// 全部转小写比较，简单实现
	if (strcasecmp(ext, "html") == 0 || strcasecmp(ext, "htm") == 0)
		return "text/html; charset=utf-8";
	else if (strcasecmp(ext, "css") == 0)
		return "text/css; charset=utf-8";
	else if (strcasecmp(ext, "js") == 0)
		return "application/javascript; charset=utf-8";
	else if (strcasecmp(ext, "txt") == 0)
		return "text/plain; charset=utf-8";
	else if (strcasecmp(ext, "csv") == 0)
		return "text/csv; charset=utf-8";
	else if (strcasecmp(ext, "xml") == 0)
		return "text/xml; charset=utf-8";
	else if (strcasecmp(ext, "json") == 0)
		return "application/json";
	else if (strcasecmp(ext, "jpg") == 0 || strcasecmp(ext, "jpeg") == 0)
		return "image/jpeg";
	else if (strcasecmp(ext, "png") == 0)
		return "image/png";
	else if (strcasecmp(ext, "gif") == 0)
		return "image/gif";
	else if (strcasecmp(ext, "svg") == 0)
		return "image/svg+xml";
	else if (strcasecmp(ext, "ico") == 0)
		return "image/x-icon";

	// 未知后缀：二进制流，下载文件
	return "application/octet-stream";
}

// 获取文件大小
off_t get_file_size_stat(const char *file)
{
	struct stat st;
	if (stat(file, &st) == -1)
		return -1;
	printf("文件大小 = %lu\n",st.st_size);
	return st.st_size;
}
//
int send_header(const char *filepath, int con_fd, res_state_t *state,int isdir)
{
	char message_buf[MESSAGE_BUFFER_SIZE];
	int total_length = 0;
	// 拼接响应头
	total_length = sprintf(message_buf, "%s %d %s\r\n", "HTTP/1.1", state->state_code, state->state_msg);
	// 设置文件长度
	total_length += sprintf(message_buf + total_length, "Content-Length: %lu\r\n", get_file_size_stat(filepath));
	// 设置文件类型
	total_length += sprintf(message_buf + total_length, "Content-Type: %s\r\n", 
		get_content_type(isdir ? "*.html" :filepath));
	total_length += sprintf(message_buf + total_length, "%c%c", '\r', '\n');
	Write(con_fd, message_buf, total_length);
	return (EXIT_SUCCESS);
}

static int filter_file(const struct dirent* filename){
	return strcmp(filename->d_name,".");
}

int send_resource(char* filepath,int isdir,char * dirpath,int con_fd){
	signal(SIGPIPE,SIG_IGN);
	char message_buf[MESSAGE_BUFFER_SIZE];
	ssize_t total_length=0;
	//文件夹的处理,找出文件夹下的所有文件，返回一个列表
	if(isdir){
		struct dirent ** files;
		//渲染界面
		/* <!DOCTYPE html>
			<html lang="en">

				<head>
					<meta charset="UTF-8">
					<meta name="viewport" content="width=device-width, initial-scale=1.0">
					<title>所有文件</title>
				</head>

				<body>
					<a href="/index.html">../</a><br/>
					<a href="/dirs/导航页.html">导航页.html</a><br/>
					<a href="/dirs/no_page.html">no_page.html</a><br/>
					<a href="/dirs/喜当爹.html">喜当爹.html</a>
				</body>
			</html> 
*/
		int file_cnt = scandir(filepath,&files,filter_file,alphasort);
		total_length = sprintf(message_buf,"%s",
		"<!DOCTYPE html> \
			<html lang=\"en\"> \
				<head> \
					<meta charset=\"UTF-8\"> \
					<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> \
					<title>所有文件</title> \
				</head><body>");
		Write(con_fd,message_buf,total_length);
		while (file_cnt--)
		{
			printf("file_name = %s\n",files[file_cnt]->d_name);
			printf("file type = %d\n",files[file_cnt]->d_type);
			if(files[file_cnt]->d_type == DT_REG)
				total_length = sprintf(message_buf,"<li><a href=\"%s/%s\">%s</a></li><br/>",dirpath,files[file_cnt]->d_name,files[file_cnt]->d_name);
			else
				total_length = sprintf(message_buf,"<li><a href=\"%s%s/\">%s</a></li><br/>",dirpath,files[file_cnt]->d_name,files[file_cnt]->d_name);
				free(files[file_cnt]);
			Write(con_fd,message_buf,total_length);
		}
		total_length = sprintf(message_buf,"%s","</body> \
			</html> ");
		Write(con_fd,message_buf,total_length);
		free(files);
		goto ret_success;
	}
	FILE * fptr = fopen(filepath, "rb");
	while (1)
	{
		total_length = fread(message_buf, sizeof(char), sizeof(message_buf), fptr);
		if (total_length == 0)
			break;
		ssize_t send_size = 0;
		while (send_size < total_length)
		{
		 	send_size +=Write(con_fd, message_buf, total_length);
		}
		printf("已发送的文件大小是否与读到的相同 = %d\n",send_size == total_length);
	}
	
	fclose(fptr);
ret_success:
	return (EXIT_SUCCESS);
}

// 处理GET请求
int handler_get_request(char *resource_url, int con_fd)
{
	char file_path[128] = STATIC_HOME_DIR;
	off_t file_length = 0;
	if (strcmp("/", resource_url) == 0)
		resource_url = "/index.html";
	strcat(file_path, resource_url);
	printf("file_path = %s\n", file_path);
	// 文件不存在，抛404
	struct stat st;
	res_state_t state;
	int isdir = 0;
	if (stat(file_path, &st) == -1)
	{
		state.state_code = 404;
		strcpy(state.state_msg, "Not Found");
		strcpy(file_path, STATIC_HOME_DIR "/not_found.html");
	}
	else
	{
		// 如果请求的是文件夹，需要回填文件夹的互动html界面
		if (S_ISDIR(st.st_mode))
			isdir = 1;
		// 如果请求的是普通文件,直获取对应url下的文件，组包发送
		printf("请求的文件路径 = %s\n", file_path);
		// 设置状态码与状态信息
		strcpy(state.state_msg, "OK");
		state.state_code = 200;
	}
	// 需要再次判断请求的文件是目录还是普通文件
	// 开始读取文件内容.
	//发送头部
	send_header(file_path,con_fd,&state,isdir);
	send_resource(file_path,isdir,resource_url, con_fd);
	return 0;
}

// 解析http请求
int parse_http_request(int con_fd, char *recv_buffer, int r_len, char *error_buf)
{
	char *error_message;
	char sub_str_buf[1024];
	char *sub_str = "\r\n";
	char request_type[8], request_resource[50];
	// 解析请求类型、请求资源
	// 1、使用strstr、strtok函数截取
	// 获取\r\n的位置
	/*
	char* ptr = strstr(recv_buffer,sub_str);
	printf("ptr == %d\n",ptr != NULL);
	if(!ptr){
		error_message = "http request format error!";
		goto failure_return;
	}
	uint32_t sub_len = (uint32_t)(ptr-recv_buffer);
	memcpy(sub_str_buf,recv_buffer,sub_len);
	sub_str_buf[sub_len] = 0;
	printf("数据=%s\n",sub_str_buf);
	//解析请求头：请求类型，资源
	char * pch;
	pch = strtok(sub_str_buf," ");
	//获取请求类型
	if(!pch){
		error_message = "get request type error!";
		goto failure_return;
	}
	strcpy(request_type,pch);
	pch = strtok(NULL," ");
	//获取请求的文件路径
	if(!pch){
		error_message = "get request resource url error!";
		goto failure_return;
	}
	strcpy(request_resource,pch);
	*/
	// 2、使用sscanf按照表达式截取
	sscanf(recv_buffer, "%[^ ] %[^ ]", request_type, request_resource);
	printf("请求类型 = %s\n", request_type);
	printf("请求资源 = %s\n", request_resource);
	utf_8_decoder(request_resource,request_resource);
	// 根据请求资源查找路径下的文件，读取文件发送
	if (strcasecmp(request_type, "GET") == 0)
		handler_get_request(request_resource, con_fd);
	return 0;
failure_return:
	sprintf(error_buf, "%s", error_message);
	return -1;
}