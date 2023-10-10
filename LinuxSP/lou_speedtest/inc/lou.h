#ifndef _LOU_H
#define _LOU_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#define SPEEDTEST_DOMAIN_NAME "www.speedtest.net"
#define CONFIG_REQUEST_URL "speedtest-config.php"   // host position url

#define SPEEDTEST_SERVERS_DOMAIN_NAME "c.speedtest.net"
#define SERVERS_LOCATION_REQUEST_URL "speedtest-servers-static.php?"    // nearly server for speedtest

#define FILE_DIRECTORY_PATH "/tmp/"
#define NEAREST_SERVERS_NUM 7
#define THREAD_NUMBER 4
#define SPEEDTEST_DURATION 5

#define UL_BUFFER_SIZE 8192
#define UL_BUFFER_TIMES 10240
#define DL_BUFFER_SIZE 8192


typedef struct client_data {
    char ipAddr[128];
    double latitude;
    double longitude;
    char isp[128];
} client_data_t;

typedef struct server_data {
    char url[128];
    double latitude;
    double longitude;
    char name[128];
    char country[128];
    double distance;
    int latency;
    long double rtt;
    char domain_name[128];
    struct sockaddr_in servinfo;
} server_data_t;

typedef struct thread {
    int thread_index;
    int running;                                                                                                              
    pthread_t tid;
    char domain_name[128];
    char request_url[128];
    struct sockaddr_in servinfo;
} thread_t;


#endif