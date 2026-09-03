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
// int send_header(const char *filepath,bufferevent_t* bev, res_state_t *state,int isdir)
// {
// 	char *message_buf = malloc(MESSAGE_BUFFER_SIZE);
// 	if(!message_buf){
// 		perror("malloc buf space error");
// 		return -1;
// 	}
// 	int total_length = 0;
// 	// 拼接响应头
// 	total_length = sprintf(message_buf, "%s %d %s\r\n", "HTTP/1.1", state->state_code, state->state_msg);
// 	// 设置文件长度
// 	total_length += sprintf(message_buf + total_length, "Content-Length: %lu\r\n", get_file_size_stat(filepath));
// 	// 设置文件类型
// 	total_length += sprintf(message_buf + total_length, "Content-Type: %s\r\n", 
// 		get_content_type(isdir ? "*.html" :filepath));
// 	total_length += sprintf(message_buf + total_length, "%c%c", '\r', '\n');
// 	bufferevent_write(bev,message_buf,total_length);
// 	free(message_buf);
// 	return (EXIT_SUCCESS);
// }

int send_header(const char *filepath,bufferevent_t* bev, res_state_t *state,int isdir,dir_padding_t* dpt)
{
	//获取输出缓冲区，往其中写入数据
 	struct evbuffer* out_buf =  bufferevent_get_output(bev);
	evbuffer_add_printf(out_buf,"%s %d %s\r\n","HTTP/1.1", state->state_code, state->state_msg);
	evbuffer_add_printf(out_buf,"Content-Length: %lu\r\n",isdir ? dpt->buf_size : get_file_size_stat(filepath));
	evbuffer_add_printf(out_buf,"Content-Type: %s\r\n\r\n",get_content_type(isdir ? "*.html" :filepath));
	return (EXIT_SUCCESS);
}

static int filter_file(const struct dirent* filename){
	return strcmp(filename->d_name,".");
}
//当请求的文件为文件夹时,填充HTML界面
int padding_dir_html(char* filepath,dir_padding_t* dpt,char* dirpath){
	char * html_buf = malloc(MESSAGE_BUFFER_SIZE);
	if(!html_buf){
		printf("malloc html buffer error");
		return -1;
	}
	dpt->msg_buf = html_buf;
	struct dirent ** files;
	int file_cnt = scandir(filepath,&files,filter_file,alphasort);
	int total_size=0;
	total_size+= sprintf(html_buf,"<!DOCTYPE html> \
			<html lang=\"en\"> \
				<head> \
					<meta charset=\"UTF-8\"> \
					<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> \
					<title>所有文件</title> \
				</head><body>");
	while (file_cnt--)
	{
		printf("file_name = %s\n",files[file_cnt]->d_name);
		printf("file type = %d\n",files[file_cnt]->d_type);
		total_size+= sprintf(html_buf+ total_size,
			"<li><a href=\"%s%s\">%s</a></li><br>",
			dirpath,files[file_cnt]->d_name,files[file_cnt]->d_name);
		free(files[file_cnt]);
	}
	total_size+= sprintf(html_buf+total_size,"</body> \
			</html>");
	dpt->buf_size =total_size;
	free(files);
	return 0;
}

void dir_padding_free(dir_padding_t * dpt){
	if(dpt->msg_buf){
		free(dpt->msg_buf);
		dpt->msg_buf=NULL;
		dpt->buf_size=0;
	}
}

int send_resource(char* filepath,int isdir,dir_padding_t* dpt ,bufferevent_t* bev){
	struct evbuffer* out_put =  bufferevent_get_output(bev);
	// signal(SIGPIPE,SIG_IGN);
	//如果是文件夹，直接发送buffer
	if(isdir){
		evbuffer_add(out_put,dpt->msg_buf,dpt->buf_size);
		goto ret_success;
	}
	int fd = open(filepath, O_RDONLY);
	evbuffer_add_file(out_put,fd,SEEK_SET,-1);
ret_success:
	return (EXIT_SUCCESS);
}

// 处理GET请求
int handler_get_request(char *resource_url, bufferevent_t* bev)
{
	char file_path[FILE_NAME_MAX_SIZE] = STATIC_HOME_DIR;
	off_t file_length = 0;
	if (strcmp("/", resource_url) == 0)
		resource_url = "/index.html";
	strcat(file_path, resource_url);
	printf("file_path = %s\n", file_path);
	// 文件不存在，抛404
	struct stat st;
	res_state_t state;
	int isdir = 0;
	dir_padding_t dpt;
	bzero(&dpt,sizeof(dpt));
	if (stat(file_path, &st) == -1)
	{
		state.state_code = 404;
		strcpy(state.state_msg, "Not Found");
		strcpy(file_path, STATIC_HOME_DIR "/not_found.html");
	}
	else
	{
		// 如果请求的是文件夹，需要回填文件夹的互动html界面
		if (S_ISDIR(st.st_mode)){
			isdir = 1;
			if(file_path[strlen(file_path)-1] !='/')
				strcat(resource_url,"/");
			int padding_state = padding_dir_html(file_path,&dpt,resource_url);
			if(padding_state == -1){
				printf("padding dir html error");
				return -1;
			}
		}
		// 如果请求的是普通文件,直获取对应url下的文件，组包发送
		printf("请求的文件路径 = %s\n", file_path);
		// 设置状态码与状态信息
		strcpy(state.state_msg, "OK");
		state.state_code = 200;
	}
	// 需要再次判断请求的文件是目录还是普通文件
	// 开始读取文件内容.
	//发送头部
	send_header(file_path,bev,&state,isdir,&dpt);
	send_resource(file_path,isdir,&dpt, bev);
	if(dpt.buf_size)
		dir_padding_free(&dpt);
	return 0;
}

// 解析http请求
int parse_http_request(bufferevent_t* bev, char *recv_buffer, int r_len, char *error_buf)
{
	fprintf(stdout,"message : %s\n",recv_buffer);
	// char *error_message;
	char request_type[METHOD_SIZE], request_resource[FILE_NAME_MAX_SIZE];
	// 获取请求类型与请求的资源
	sscanf(recv_buffer, "%[^ ] %[^ ]", request_type, request_resource);
	utf_8_decoder(request_resource,request_resource);
	printf("请求类型 = %s\n", request_type);
	printf("请求资源 = %s\n", request_resource);
	// 根据请求资源查找路径下的文件，读取文件发送
	if (strcasecmp(request_type, "GET") == 0)
		handler_get_request(request_resource, bev);
	return 0;
// failure_return:
// 	sprintf(error_buf, "%s", error_message);
// 	return -1;
}