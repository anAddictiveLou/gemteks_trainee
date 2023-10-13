#ifndef _HTTP_H
#define _HTTP_H

#include "lou.h"

int get_http_file(struct sockaddr_in *serv, char *domain_name, char *request_url, char *filename);

#endif