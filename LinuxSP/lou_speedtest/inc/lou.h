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
#define NEAREST_SERVERS_NUM 5s
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

extern float start_dl_time;
extern float stop_dl_time;
extern float start_ul_time;
extern float stop_ul_time;
extern int thread_all_stop;
extern long int total_dl_size;
extern long int total_ul_size;

extern pthread_mutex_t pthread_mutex; 
extern thread_t thread[THREAD_NUMBER];


float get_uptime(void);
int get_ipv4_addr(char *domain_name, struct sockaddr_in *servinfo);
int get_http_file(struct sockaddr_in *serv, char *domain_name, char *request_url, char *filename);
int get_ip_address_position(char *fileName, client_data_t *client_data);
double calcDistance(double lat1, double lon1, double lat2, double lon2);
int get_nearest_server(double lat_c, double lon_c, server_data_t *nearest_servers);
int get_best_server(server_data_t *nearest_servers);



#endif