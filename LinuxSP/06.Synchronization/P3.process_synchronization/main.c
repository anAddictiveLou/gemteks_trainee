#include <semaphore.h>
#include <pthread.h>    
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_VALUE 20
#define MAX_LOG 100

char log_msg[MAX_LOG];
char buffer[MAX_LOG];
char c;
int fd;
int pid;
off_t file_size;
int* shared_var;

void* alloc_shared_mem(size_t size)
{
    void* ptr = NULL;
    int shm_fd = shm_open("shared_mem", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, size);
    ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    memset(ptr, 0, size);
    return ptr;
}

void reverseString(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}


void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        if (*shared_var > MAX_VALUE)
        {    
            return;
        }
        memset(log_msg, 0, MAX_LOG);
        
        /* get file size */
        file_size = lseek(fd, 0, SEEK_END);
        int idx = 0;

        /* read last shared var */
        while (file_size >= 0)
        {
            file_size--;
            lseek(fd, file_size, SEEK_SET);
            read(fd, &buffer[idx++], 1);
            if (buffer[idx-1] == ' ')
            {
                buffer[idx-1] == '\0';
                break;
            }
        }

        /* reverse string to get right value */
        reverseString(buffer);
        *shared_var = atoi(buffer) + 1;
        memset(buffer, 0, MAX_LOG);

        /* write again to file */
        snprintf(log_msg, MAX_LOG, "pid = %d, var = %d\n", getpid(), *shared_var);
        write(fd, log_msg, strlen(log_msg));


        kill(getppid(), SIGUSR1);
    }
}


int main(int argc, char** argv)
{
    shared_var = (int*) alloc_shared_mem(sizeof(int));
    fd = open("log_file", O_APPEND | O_RDWR | O_CREAT, 0666);
    snprintf(log_msg, MAX_LOG, "pid = %d, var = %d\n", getpid(), *shared_var);
    write(fd, log_msg, strlen(log_msg));

    signal(SIGUSR1, signal_handler);

    pid = fork();
    switch (pid)
    {
    case -1:
        printf("fork() failed\n");
        exit(EXIT_FAILURE);
    case 0:
        /* in child process */
        while(1)
        {   
            pause();
        }
        exit(EXIT_SUCCESS);
    default:
        /* in parent process */
        while(1)
        {
            kill(pid, SIGUSR1);
            pause();
        }
        break;
    }
    wait(NULL);
    shm_unlink("shared_mem");
    exit(EXIT_SUCCESS);
}