#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
    printf("pid: %d\n", getpid());
    if(signal(SIGINT, SIG_IGN) == SIG_ERR){
        fprintf(stderr, "signal(SIGINT, SIG_IGN); failed\n");
        exit(EXIT_FAILURE);
    }
    
    while(1);
    return 0;
}