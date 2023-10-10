#ifndef _UPLOAD_H
#define _UPLOAD_H

#include "lou.h"

void *calculate_ul_speed_thread();
void *upload_thread(void *arg);
int speedtest_upload(server_data_t *nearest_server);

#endif