#ifndef _DOWNLOAD_H
#define _DOWNLOAD_H

#include "lou.h"

void *calculate_dl_speed_thread();
void *download_thread(void *arg);
int speedtest_download(server_data_t *nearest_server);

#endif