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

#define NUM_OF_THREADS 5
#define NUM_OF_FILES 2
#define MAX_VALUE 20
#define MAX_LOG 100

/* Shared resource */
int common_variable = 0;    
int fd[NUM_OF_FILES];
sem_t smp[NUM_OF_FILES];
pthread_mutex_t lock;


void* thread_handler(void* thread_arg)
{
    char log_msg[MAX_LOG];
    /* increase common variable */
    while (common_variable <= MAX_VALUE)
    {
        pthread_mutex_lock(&lock);
        memset(log_msg, 0, MAX_LOG);
        common_variable+=1;
        snprintf(log_msg, MAX_LOG, "thread id: %ld, common variable = %d\n", pthread_self(), common_variable);
        printf("%s\n", log_msg);
        pthread_mutex_unlock(&lock);
    }

    return 0;
}


int main(int argc, char** argv)
{
    pthread_t tid[NUM_OF_THREADS] = {0};

    /* Create semaphore & mutex */
    pthread_mutex_init(&lock, NULL);



    for (int i = 0; i < NUM_OF_THREADS; i++)
    {
        if ( pthread_create(&tid[i], NULL, thread_handler, NULL) != 0 )
        {
            perror("create thread failed\n");
            exit(EXIT_FAILURE);
        }       
    }

    for (int i = 0; i < NUM_OF_THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    exit(EXIT_SUCCESS);
}