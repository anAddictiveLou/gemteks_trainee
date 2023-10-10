#include "main.h"

void stop_all_thread(int signo) {
    if(signo == SIGALRM) {
        thread_all_stop=1;
    }
    return;
}

int main() {
    int i, best_server_index;
    client_data_t client_data;
    server_data_t nearest_servers[NEAREST_SERVERS_NUM];
    pthread_t pid;
    struct sockaddr_in servinfo;
    struct itimerval timerVal;

    memset(&client_data, 0, sizeof(client_data_t));
    for(i=0; i<NEAREST_SERVERS_NUM; i++) {
        memset(&nearest_servers[i], 0, sizeof(server_data_t));
    }

    if(get_ipv4_addr(SPEEDTEST_DOMAIN_NAME, &servinfo)) {
        if(!get_http_file(&servinfo, SPEEDTEST_DOMAIN_NAME, CONFIG_REQUEST_URL, CONFIG_REQUEST_URL)) {
            printf("Can't get your IP address information.\n");
            return 0;
        }
    }
    if(get_ipv4_addr(SPEEDTEST_SERVERS_DOMAIN_NAME, &servinfo)) {
        if(!get_http_file(&servinfo, SPEEDTEST_SERVERS_DOMAIN_NAME, SERVERS_LOCATION_REQUEST_URL, SERVERS_LOCATION_REQUEST_URL)) {
            printf("Can't get servers list.\n");
            return 0;
        }
    }

    get_ip_address_position(CONFIG_REQUEST_URL, &client_data);
    printf("============================================\n");
    printf("Your IP Address : %s\n", client_data.ipAddr);
    printf("Your IP Location: %0.4lf, %0.4lf\n", client_data.latitude, client_data.longitude);
    printf("Your ISP        : %s\n", client_data.isp);
    printf("============================================\n");

    if(get_nearest_server(client_data.latitude, client_data.longitude, nearest_servers)==0) {
        printf("Can't get server list.\n"); 
        return 0;
    }
    if((best_server_index = get_best_server(nearest_servers))!=-1) {
        printf("==========The best server information==========\n");
        printf("URL: %s\n", nearest_servers[best_server_index].url);
        printf("Latitude: %lf, Longitude: %lf\n", nearest_servers[best_server_index].latitude, nearest_servers[best_server_index].longitude);
        printf("Name: %s\n", nearest_servers[best_server_index].name);
        printf("Country: %s\n", nearest_servers[best_server_index].country);
        printf("Distance: %lf (km)\n", nearest_servers[best_server_index].distance);
        printf("Latency: %d (us)\n", nearest_servers[best_server_index].latency);
        printf("===============================================\n");
        //Set speed test timer
        signal(SIGALRM, stop_all_thread);
        alarm(SPEEDTEST_DURATION);
        // timerVal.it_value.tv_sec = SPEEDTEST_DURATION;
        // timerVal.it_value.tv_usec = 0;
        // setitimer(ITIMER_REAL, &timerVal, NULL); 
    
        pthread_create(&pid, NULL, calculate_dl_speed_thread, NULL);
        speedtest_download(&nearest_servers[best_server_index]);

        sleep(2);
        printf("\n");
        thread_all_stop=0;
        alarm(SPEEDTEST_DURATION);
        //setitimer(ITIMER_REAL, &timerVal, NULL);

        pthread_create(&pid, NULL, calculate_ul_speed_thread, NULL);
        speedtest_upload(&nearest_servers[best_server_index]);
        printf("\n");
    }
    else 
    {
        printf("All server can not run speedtest\n");
    }
    return 0;
}
