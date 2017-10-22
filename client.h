#ifndef CLIENT_H
#define CLIENT_H

#include "threadlist.h"

enum rq_method {
	RQ_METHOD_GET,
	RQ_METHOD_UNSUPPORTED
};

enum rq_compression {
	RQ_COMP_GZ = 1,
	RQ_COMP_DEFLATE = 2
};

struct rq {
	char * path, * syspath;
	enum rq_method method;
	enum rq_compression supported_compression;
	int line_recv;
	char pv_maj, pv_min;
};

void rq_free(struct rq * rq);
void rq_thread_cleanup(void * data);
int rq_parse_method(struct rq * rq, char * line, char ** rest);
int rq_parse_path(struct rq * rq, char * line, char ** rest);
int rq_is_hdr(char * header_name, char * line, char ** rest);
int rq_200(struct rq * rq, int socket_fd, FILE * file, char * mimetype, int length);
int rq_404(struct rq * rq, int socket_fd, char * msg);
int str_ends_with(char * str, char * end);
char * rq_mime_type(char * path);
int rq_handle(struct rq * rq, int socket_fd);
int rq_line(struct rq * rq, char * line, int socket_fd);
void * thread_client(void * arg);

#endif