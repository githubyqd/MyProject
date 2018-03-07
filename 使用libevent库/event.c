#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <event2/event.h>
#include <fcntl.h>
#include <sys/stat.h>

void cb_func(evutil_socket_t fd, short what, void *arg)
{
	const char *data = arg;
	printf("Got an event on socket %d:%s%s%s%s [%s]\n",
		(int) fd,
		(what&EV_TIMEOUT) ? " timeout" : "",
		(what&EV_READ) ? " read" : "",
		(what&EV_WRITE) ? " write" : "",
		(what&EV_SIGNAL) ? " signal" : "",
		data
	);
}

void main_loop(evutil_socket_t fd1, evutil_socket_t fd2)
{
	struct event *ev1, *ev2;
	struct timeval five_seconds = {5, 0};
	struct event_base *base = event_base_new();
	
	//监听是否可读，设置超时持续监听
	ev1 = event_new(base, fd1, EV_TIMEOUT|EV_READ|EV_PERSIST, cb_func, (char*)"Reading event");
	ev2 = event_new(base, fd2, EV_WRITE|EV_PERSIST, cb_func, (char*)"Writing event");
	
	//让事件处于未决状态
	event_add(ev1, &five_seconds);
	event_add(ev2, NULL);
	
	event_base_dispatch(base);	//监听base
}

int main(int argc, char *argv[])
{
	const char *fifo = "event.fifo";
	int fd1, fd2;
	
	unlink(fifo);  		//确保fifo不存在
	if(mkfifo(fifo, 0644))
	{
		perror("mkfifo err");
		exit(1);
	}
	
	fd1 = open(fifo, O_RDONLY|O_NONBLOCK, 0644);
	if(fd1 < 0)
	{
		perror("open err");
		exit(1);
	}
	fd2 = open(fifo, O_WRONLY|O_NONBLOCK, 0644);
	if(fd2 < 0)
	{
		perror("open err");
		exit(1);
	}
	
	main_loop(fd1, fd2);
	
	close(fd1);
	close(fd2);
	return 0;
}

