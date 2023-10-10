#ifndef _MAIN_H
#define _MAIN_H

#include "lou.h"
#include "download.h"
#include "upload.h"


float start_dl_time, stop_dl_time, start_ul_time, stop_ul_time;
int thread_all_stop=0;
long int total_dl_size=0, total_ul_size=0;

pthread_mutex_t pthread_mutex = PTHREAD_MUTEX_INITIALIZER; 
thread_t thread[THREAD_NUMBER];


#endif