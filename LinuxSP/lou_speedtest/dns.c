#ifndef _DNS_H
#define _DNS_H
#include "lou.h"

int get_ipv4_addr(char *domain_name, struct sockaddr_in *servinfo) 
{    
    /* issue 1: dommain name can not be resolution if have :8080 */
    struct addrinfo hints, *addrinfo, *p;
    int status;

    printf("PRINT_LOG: %s\n", domain_name);
    char* token =  strtok(domain_name, ":");

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;


    /*change1:  change domain_name to token*/
    if((status = getaddrinfo(token, "http", &hints, &addrinfo)) != 0) {
        printf("Resolve DNS Failed: Can't get ip address! (%s)\n", token);
        return 0;
    }

    for(p=addrinfo; p!=NULL; p=p->ai_next) {
        if(p->ai_family == AF_INET) {
            memcpy(servinfo, (struct sockaddr_in *)p->ai_addr, sizeof(struct sockaddr_in));
        }
    }
    freeaddrinfo(addrinfo);
    return 1;
}

#endif