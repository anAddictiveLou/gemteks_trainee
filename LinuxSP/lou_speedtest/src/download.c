#include "download.h"

void *calculate_dl_speed_thread() {
    double dl_speed=0.0, duration=0;
    while(1) {
        stop_dl_time = get_uptime();
        duration = stop_dl_time-start_dl_time;
        //dl_speed = (double)total_dl_size/1024/1024/duration*8;
        dl_speed = (double)total_dl_size/1000/1000/duration*8;
        if(duration>0) {
            printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bDownload speed: %0.2lf Mbps", dl_speed);
            fflush(stdout);
        }
        usleep(500000);

        if(thread_all_stop) {
            stop_dl_time = get_uptime();
            duration = stop_dl_time-start_dl_time;
            //dl_speed = (double)total_dl_size/1024/1024/duration*8;
            dl_speed = (double)total_dl_size/1000/1000/duration*8;
            if(duration>0) {
                printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bDownload speed: %0.2lf Mbps", dl_speed);
                fflush(stdout);
            }   
            break;
        }
    }
    return NULL;
}

void *download_thread(void *arg) {
    thread_t *t_arg = arg;
    int i = t_arg->thread_index;

    int fd;
    char sbuf[256]={0}, rbuf[DL_BUFFER_SIZE];
    struct timeval tv;
    fd_set fdSet;

    if((fd = socket(thread[i].servinfo.sin_family, SOCK_STREAM, 0)) == -1) {                                                  
        perror("Open socket error!\n");
        goto err;
    }

    if(connect(fd, (struct sockaddr *)&thread[i].servinfo, sizeof(struct sockaddr)) == -1) {
        perror("Socket connect error!\n");
        goto err;
    }

    sprintf(sbuf,
            "GET /%s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "User-Agent: status\r\n"
            "Accept: */*\r\n\r\n", thread[i].request_url, thread[i].domain_name);

    if(send(fd, sbuf, strlen(sbuf), 0) != strlen(sbuf)) {
        perror("Can't send data to server\n");
        goto err;
    }

    while(1) {
        FD_ZERO(&fdSet);
        FD_SET(fd, &fdSet);

        tv.tv_sec = 3;
        tv.tv_usec = 0;
        int status = select(fd + 1, &fdSet, NULL, NULL, &tv);                                                         

        int recv_byte = recv(fd, rbuf, sizeof(rbuf), 0);
        if(status > 0 && FD_ISSET(fd, &fdSet)) {
            if(recv_byte < 0) {
                printf("Can't receive data!\n");
                break;
            } else if(recv_byte == 0){
                break;
            } else {
                pthread_mutex_lock(&pthread_mutex);
                total_dl_size+=recv_byte;
                pthread_mutex_unlock(&pthread_mutex);
            }

            if(thread_all_stop)
                break;
        }   
    }

err: 
    if(fd) close(fd);
    thread[i].running=0;
    return NULL;
}

int speedtest_download(server_data_t *nearest_server) {
    const char download_filename[64]="random3500x3500.jpg";  //23MB
    char url[128]={0}, request_url[128]={0}, dummy[128]={0}, buf[128];
    char *ptr=NULL;
    int i;

    sscanf(nearest_server->url, "http://%[^/]/%s", dummy, request_url);
    strncpy(url, request_url, sizeof(request_url));
    memset(request_url, 0, sizeof(request_url));

    ptr = strtok(url, "/");
    while(ptr!=NULL) {
        memset(buf, 0, sizeof(buf));
        strncpy(buf, ptr, strlen(ptr));

        //Change file name
        if(strstr(buf, "upload.")!=NULL) {
            strcat(request_url, download_filename);
        } else {
            strcat(request_url, buf);
            strcat(request_url, "/");
        }
        ptr = strtok(NULL, "/");
    }

    start_dl_time = get_uptime();
    while(1) {
        for(i=0; i<THREAD_NUMBER; i++) {
            memcpy(&thread[i].servinfo, &nearest_server->servinfo, sizeof(struct sockaddr_in));
            memcpy(&thread[i].domain_name, &nearest_server->domain_name, sizeof(nearest_server->domain_name));
            memcpy(&thread[i].request_url, request_url, sizeof(request_url));
            if(thread[i].running == 0) {
                thread[i].thread_index = i;
                thread[i].running = 1;
                pthread_create(&thread[i].tid, NULL, download_thread, &thread[i]);
            }
        }
        if(thread_all_stop)
            break;
    }
    return 1;
}
