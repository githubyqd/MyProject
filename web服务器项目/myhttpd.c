#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>

#define SERVER_NAME "myhttpd"
#define PROTOCOL "HTTP/1.1"
#define SERVER_URL "http://www.baidu.com/"
#define FORMAT_DATE "%a, %d %b %Y %H:%M:%S GMT"
#define N 4096

//#ifdef DEBUG

#define log(info, str)\
	do{\
		fprintf(fp_tmp, "%s%s", info, str);\
		fflush(fp_tmp);\
	}while(0)

//put them in the right place.
//fp_tmp = fopen(/home/yqd/dir/log.text, "a");
//log("argv[1]", argv[1]);
//log("line:", line);
//#endif

static void send_headers(int status, char* title, char* extra_header, char* mime_type, off_t length, time_t mod);
static void send_error(int status, char *title, char* extra_header, char *text);
static void strencode(char *to,size_t tosize, const char *from);
static void file_infos(char *dir, char *name);
static void strdecode(char *to, char *from);
static char *get_mime_type(char *name);
static int hexit(char c);

int main(int argc, char **argv)
{
	char line[N*2], method[N*2], path[N*2], protocol[N*2], idx[N*4], location[N*4];
	char *file;
	size_t len;
	int ich, i, n, ret;
	struct stat sbuf;
	FILE *fp;
	struct dirent **dl;
	char *type;

	if(argc != 2)
		send_error(500, "Internal Error", NULL, "Config error - no dir specified.");

	if(chdir(argv[1]) < 0)
		send_error(500, "Internal Error", NULL, "Config error - couldn't chdir().");

	if(fgets(line, sizeof(line), stdin) == NULL)		//stdin被dup2到xinetd管道的读端
	{
		send_error(400, "Bad Requst", NULL, "No requst found.");
	}
	if(sscanf(line, "%[^ ] %[^ ] %[^ ]", method, path, protocol) != 3)
	send_error(400, "Bad Requst", NULL, "Can't parse requst.");

	while(fgets(line, sizeof(line), stdin) != NULL)
	{
		if(strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0)
		break;
	}

	if(strcasecmp(method, "GET") != 0)
	send_error(501, "Not Implemented", NULL, "The method is not implemented.");

	if(path[0] != '/')	
	send_error(400, "Bad Requst", NULL, "Bad filename.");

	file = &(path[1]);
	
	strdecode(file, file);

	if(file[0] == '\0')
		file = "./";
	len = strlen(file);
	if(file[0] == '/' || strcmp(file, "..") == 0
			  || strncmp(file, "../", 3) == 0
			  || strstr(file, "/../") != NULL
			  || strcmp(&file[len-3], "/..") == 0)
		send_error(400, "Not Found", (char*)0, "Illegal filename.");
#if 1
	FILE *fp_tmp = fopen("/home/yyyy/fp_tmp.txt", "a");
	if(fp_tmp == NULL)
	{
		perror("open fp_tmp.txt error");
		exit(1);
	}
	log("path+1:", path+1);
	fclose(fp_tmp);
#endif
	ret = stat(file, &sbuf);
	if(ret != 0)
	{
		send_error(404, "Not Found", (char*)0, "file not found");
	}
	if(S_ISDIR(sbuf.st_mode))
	{
		if(file[len-1] != '/')
		{
			snprintf(location, sizeof(location), "Location: %s/", path);
			send_error(302, "Found", location, "Directories must end with alash");
		}

		snprintf(idx, sizeof(idx), "%sindex.html", file);
		if(stat(idx, &sbuf) >= 0)
		{
			file = idx;
			goto do_file;
		}

		send_headers(200, "OK", NULL, "text/html", -1, sbuf.st_mtime);
	
		printf("<html><head><title>Index of %s</title></head>"
				"\n<body bgcolor=\"#99cc99\"><h4>Index of %s</h4>\n<pre>\n", file, file);
		n = scandir(file, &dl, NULL, alphasort);			//过滤器NULL 字母排序
		if(n < 0)
		{
			perror("scandir");
		}
		else
		{
			for(i = 0; i < n; i++)
			{
				file_infos(file, dl[i]->d_name);
			}
		}
		printf("</pre>\n<hr>\n<address><a href=\"%s\">%s</a></address>\n</body></html>\n", SERVER_URL, SERVER_NAME);
	}
	else
	{

do_file:
		fp = fopen(file, "r");
		if(fp == (FILE*)0)
		{
			send_error(403, "Forbidden", (char*)0, "File is protected.");
		}

		send_headers(200, "OK", (char*)0, get_mime_type(file), sbuf.st_size, sbuf.st_mtime);

		while((ich = getc(fp)) != EOF)
		{
			putchar(ich);
		}
	}
	fflush(stdout);
	exit(0);
}

static void file_infos(char *dir, char *name)
{
	static char encoded_name[N];
	static char path[N];
	char timestr[16];
	struct stat sbuf;
	strencode(encoded_name, sizeof(encoded_name), name);
	snprintf(path, sizeof(path), "%s/%s", dir, name);
	if(lstat(path, &sbuf) < 0)
	{
		printf("<a href=\"%s\">%-32.32s</a>\n", encoded_name, name);		//32个字符长度-左对齐
	}
	else
	{
		strftime(timestr, sizeof(timestr), "%d%b%Y %H:%M", localtime(&sbuf.st_mtime));
		printf("<a href=\"%s\">%-32.32s</a>		%15s %14ld\n", encoded_name, name, timestr, (int64_t)sbuf.st_size);
	}
}
/*
	status：错误号
	title：错误名
	text：错误描述
	extra_header：附加描述（特殊情况302时不退出程序，而直接显示正常页面）
*/

static void send_error(int status, char *title, char* extra_header, char *text)
{
	send_headers(status, title, extra_header, "text/html", -1, -1);
	printf("<html><head><title>%d %s</title></head>\n<body bgcolor=\"#cc99cc\"><h4>%d %s</h4>\n", status, title, status, title);
	printf("%s\n", text);
	printf("<hr>\n<address><a href=\"%s\">%s</a></address>\n</body>\n</html>\n", SERVER_URL, SERVER_NAME);
	fflush(stdout);
	exit(1);
}

/*
	每个HTTP传送都包含一个首部、一个空行和要发送的数据项
	Content-Type：数据项的类型（必选）
	Content-length：数据项的大小
	Content-Encoding：数据项的编码方式
	Content-Language：数据项使用的语言

	首部中的每一行都包含一个关键字、一个置号和信息
	e.g.
	Content-Type：text/html; charset=iso-8859-1		指明属性的首部
	Content-length：588
													空行
	<html>文档内容</html>							数据项
*/

static void send_headers(int status, char* title, char* extra_header, char* mime_type, off_t length, time_t mod)
{
	time_t now;
	char timebuf[100];
	printf("%s %d %s\r\n", PROTOCOL, status, title);// "HTTP/1.1", 200, "OK"
	printf("Server: %s\r\n", SERVER_NAME); //Server：myxhttpd
	now = time((time_t*)0);
	strftime(timebuf, sizeof(timebuf), FORMAT_DATE, gmtime(&now));
	printf("Date: %s\r\n", timebuf);

	//Date：Fri, 18 jul 2014 14:34:26 GTM

	if(extra_header != NULL)
	{
		printf("%s\r\n", extra_header);
	}
	
	if(mime_type != NULL)
	{
		printf("Content-Type: %s\r\n", mime_type);
	}

	if(length >= 0)
	{
		printf("Content-Length: %ld\r\n", (int64_t)length);
	}

	if(mod != (time_t)-1)
	{
		strftime(timebuf, sizeof(timebuf), FORMAT_DATE, gmtime(&mod));
	}
	printf("Conection: close\r\n");
	printf("\r\n");
}

static char* get_mime_type(char *name)
{
	char *dot;//自右向左查找‘.’字符；如不存在返回NULL
	dot = strrchr(name, '.');
	/*
		charset=iso-8859-1		西欧的编码，说明网站采用的编码是英文
		charset=gb2312			简体中文
		charset=utf-8			世界通用语言编码
		charset=euc-kr			韩文
		charset=bigs		繁体中文

		使用后缀判断传递进来的文件的文件类型
		将对应的文件类型按照http定义的关键字发送回去
	*/
	if(dot == (char*)0)
	{
		return "text/plain; charset=charset=iso-8859-1";
	}
	if(strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
	{
		return "text/html; charset=charset=iso-8859-1";
	}
	if(strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
	{
		return "image/jpeg";
	}
	if(strcmp(dot, ".gif") == 0)
	{
		return "image/gif";
	}
	if(strcmp(dot, ".png") == 0)
	{
		return "image/png";
	}
	if(strcmp(dot, ".css") == 0)
	{
		return "text/css";
	}
	if(strcmp(dot, ".au") == 0)
	{
		return "audio/basic";
	}
	if(strcmp(dot, ".wav") == 0)
	{
		return "audio/wav";
	}
	if(strcmp(dot, ".avi") == 0)
	{
		return "video/x-msvideo";
	}
	if(strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt"))
	{
		return "video/quicktime";
	}
	if(strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe"))
	{
		return "video/mpeg";
	}
	if(strcmp(dot, ".vrml") == 0 || strcmp(dot, ".vrl"))
	{
		return "model/vrml";
	}
	if(strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid"))
	{
		return "audio/midi";
	}
	if(strcmp(dot, ".mp3") == 0)
	{
		return "audio/mpeg";
	}
	if(strcmp(dot, ".ogg") == 0)
	{
		return "application/ogg";
	}
	if(strcmp(dot, ".pac") == 0)
	{
		return "application/x-ns-proxy-autoconfig";
	}
	return "text/plain; charset=iso-8859-1";
}

/*
	这里的内容是处理%20之类的东西，是解码过程
	%20 URL编码中的‘ ’
	%21 '!' %22 """ %23 '#' %24 '$'
	%25 '%' %26 '&' %27 """ %28 '(' ......
	相关知识html中的' '是&nbsp
*/
static void strdecode(char *to, char *from)
{
	for ( ; *from != '\0'; ++to, ++from)
	{
		if(from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2]))//判断from中 %20 三个字符
		{
			*to = hexit(from[1]*16 + hexit(from[2]));
			from += 2;//移过已经处理的两个字符（%21指针指向1）
		}
		else
		{
			*to = *from;
		}
	}
	*to = '\0';
}

//16进制转化为10进制，return 0不会出现
static int hexit(char c)
{
	if (c >= '0' && c <= '9')
	{
		return c - '0';
	}
	if (c >= 'a' && c <= 'f')
	{
		return c - 'a' + 10;
	}
	if (c >= 'A' && c <= 'F')
	{
		return c - 'A' + 10;
	}
	return 0;
}

//编码，用作回写浏览器时，将字母、数字、/、.、-以外的字符转以后写回去
static void strencode(char *to, size_t tosize, const char *from)
{
	int tolen;
	for (tolen = 0; *from != '\0' && tolen + 4 < tosize; ++from)
	{
		if (isalnum(*from) || strchr("/_.-~", *from) != (char*)0)
		{
			*to = *from;
			++to;
			++tolen;
		}
		else
		{
			sprintf(to, "%%%02x", (int)*from & 0xff);
			to += 3;
			tolen += 3;
		}
	}
	*to = '\0';
}



