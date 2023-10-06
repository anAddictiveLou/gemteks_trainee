#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h> 


time_t current_time;
struct tm *time_info;
char time_string[80];

void signal_handler(int signum) {

    // Get the current time
    time(&current_time);

    // Convert the current time to a local time structure
    time_info = localtime(&current_time);

    // Format the time as a string
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);

    if (signum == SIGUSR1) {
        printf("%s >> received SIGUSR1.\n", time_string);
    } else if (signum == SIGUSR2) {
        printf("%s >> received SIGUSR2.\n", time_string);
    }
}

int main() {

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    // Set up a timer to send signals at specific times
    struct sigevent sev;
    timer_t timerid;
    struct itimerspec its;

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGUSR1;
    timer_create(CLOCK_REALTIME, &sev, &timerid);

    its.it_value.tv_sec = 5;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 3;
    its.it_interval.tv_nsec = 0;

    // Start the timer
    timer_settime(timerid, 0, &its, NULL);
    
    for(;;);

    return 0;
}