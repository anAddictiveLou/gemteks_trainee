#include "http.h"


int get_http_file(struct sockaddr_in *serv, char *domain_name, char *request_url, char *filename) {
    int fd;
    char sbuf[256]={0}, tmp_path[128]={0};
    char rbuf[8192];
    struct timeval tv;
    fd_set fdSet;
    FILE *fp=NULL;


    if((fd = socket(serv->sin_family, SOCK_STREAM, 0)) == -1) {
        perror("Open socket error!\n");
        if(fd) close(fd);
        return 0;
    }

    /* set connect() time out */
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = TIMEOUT_CONNECT_IN_US;
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    if(connect(fd, (struct sockaddr *)serv, sizeof(struct sockaddr)) == -1) {
        if (errno != EINPROGRESS)
        {
            /* lou debug */
            //printf("\n\nCreate connection to %s failed!\n", domain_name);
            //perror("Error: ");
            if(fd) close(fd);
            return 0;
        }
        /* lou debug */
        //printf("Trying connect to %s\n", domain_name);
    }

    sprintf(sbuf,
            "GET /%s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "User-Agent: status\r\n"
            "Accept: */*\r\n\r\n", request_url, domain_name);                                                          

    if(send(fd, sbuf, strlen(sbuf), 0) != strlen(sbuf)) {
        /* lou debug */
        //printf("Can't send data to %s\n", domain_name);
        if(fd) close(fd);
        return 0;
    }

    sprintf(tmp_path, "%s%s", FILE_DIRECTORY_PATH, filename);
    fp = fopen(tmp_path, "w+");

    while(1) {
        char *ptr=NULL;
        memset(rbuf, 0, sizeof(rbuf));
        FD_ZERO(&fdSet);
        FD_SET(fd, &fdSet);
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        int status = select(fd + 1, &fdSet, NULL, NULL, &tv);
        int i = recv(fd, rbuf, sizeof(rbuf), 0);
        if(status > 0 && FD_ISSET(fd, &fdSet)) {
            if(i < 0) {
                printf("Can't get http file!\n");
                close(fd);
                fclose(fp);
                return 0;
            } else if(i == 0) {
                break;
            } else {
                if((ptr = strstr(rbuf, "\r\n\r\n")) != NULL) {
                    ptr += 4;
                    fwrite(ptr, 1, strlen(ptr), fp);
                } else {
                    fwrite(rbuf, 1, i, fp);
                }
            }
        }
    }
    close(fd);
    fclose(fp);
    return 1;
}
