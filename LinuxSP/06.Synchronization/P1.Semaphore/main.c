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

#define NUM_OF_THREADS 3
#define NUM_OF_FILES 2
#define MAX_VALUE 200
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
        pthread_mutex_unlock(&lock);

        /* write log msg 1 of 2 files */
        srand(time(NULL));
        int random_fd = rand() % 2;
        if (random_fd == 0)
        {
            sem_wait(&smp[0]);
            write(fd[0], log_msg, strlen(log_msg));
            sem_post(&smp[0]);
        }
        else
        {
            sem_wait(&smp[1]);
            write(fd[1], log_msg, strlen(log_msg));
            sem_post(&smp[1]);
        }
    }



    return 0;
}


int main(int argc, char** argv)
{
    pthread_t tid[NUM_OF_THREADS] = {0};

    /* Create semaphore & mutex */
    sem_init(&smp[0], 0, 1);
    sem_init(&smp[1], 0, 1);
    pthread_mutex_init(&lock, NULL);

    /* open file */
    fd[0] = open("out1", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    fd[1] = open("out2", O_CREAT | O_WRONLY | O_TRUNC, 0666);


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
    sem_destroy(&smp[0]);
    sem_destroy(&smp[1]);
    close(fd[0]);
    close(fd[1]);

    exit(EXIT_SUCCESS);
}