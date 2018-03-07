#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static void echo_read_cb(struct bufferevent *bev, void *ctx)
{
	struct evbuffer *input = bufferevent_get_input(bev);
	struct evbuffer *output = bufferevent_get_output(bev);
	evbuffer_add_buffer(output, input);
}

static void echo_event_cb(struct bufferevent *bev, short events, void *ctx)
{
	if(events & BEV_EVENT_ERROR)
	{
		perror("error from bufferevent");
	}
	if(events & (BEV_EVENT_EOF|BEV_EVENT_ERROR))
	{
		bufferevent_free(bev);
	}
}

static void accept_conn_cb(struct evconnlistener *listener,
	evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx)
{
	struct event_base *base = evconnlistener_get_base(listener);
	
	//创建一个bufferevent绑定fd和base
	struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	
	//注册回调
	bufferevent_setcb(bev, echo_read_cb, NULL, echo_event_cb, NULL);
	
	//启动监听
	bufferevent_enable(bev, EV_READ|EV_WRITE);
}

static void accept_error_cb(struct evconnlistener *listener, void *ctx)
{
	struct event_base *base = evconnlistener_get_base(listener);
	int err = EVUTIL_SOCKET_ERROR();
	fprintf(stderr, "Got an error %d (%s) on the listener. "
		"Shutting down.\n", err, evutil_socket_error_to_string(err));
	event_base_loopexit(base, NULL);
}

int main(int argc, char **argv)
{
	struct event_base *base;
	struct evconnlistener *listener;
	struct sockaddr_in sin;
	int port = 9876;
	
	if(argc > 1)
	{
		port = atoi(argv[1]);
	}
	if(port<=0 || port>65535)
	{
		puts("Invalid port");
		return 1;
	}
	
	//创建一个句柄，在内核开辟一个监听事件的根结点
	base = event_base_new();
	if(!base)
	{
		puts("Couldn't open event base");
		return 1;
	}
	
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(0);
	sin.sin_port = htons(port);
	
	listener = evconnlistener_new_bind(base, accept_conn_cb, NULL, 
		LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1, 
		(struct sockaddr*)&sin, sizeof(sin));
	if(!listener)
	{
		perror("couldn't create listener");
		return 1;
	}
	evconnlistener_set_error_cb(listener, accept_error_cb);
	
	//开启循环监听
	event_base_dispatch(base);
	
	return 0;
}

