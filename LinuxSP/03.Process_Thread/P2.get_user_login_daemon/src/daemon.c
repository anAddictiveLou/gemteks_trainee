#include "daemon.h"


void create_daemon(void* (*daemon_job)(void*), void* arg)
{
    /* Step7: Ignore the SIGHUP signal */
    signal(SIGHUP, SIG_IGN);  

    /* Step1: Make the process child of systemd */
    pid_t cpid = fork();
    if (cpid > 0)
        exit(EXIT_SUCCESS);

    /* Step2: Close all files descriptors except 0, 1, 2 */
    struct rlimit r;
    getrlimit(RLIMIT_NOFILE, &r);
    for (int i = 3; i < r.rlim_max; i++)
        close(i);
    
    /* Step3: only a single instance of a daemon process should run */
    int fd = open("f1.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd == -1)
        perror("open");
    struct flock lock;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    int rv = fcntl(fd, F_SETLK, &lock);
    if (rv == -1)
    {
        printf("This process is already running\n");
        close(fd);
        exit(1);
    }
    fprintf(stderr, "Daemon has started running with PID: %d\n", getpid());


    /* Step4: Make stdio point to /dev/null */
    int fd0 = open("/dev/null", O_RDWR);
    dup2(fd0, 0);
    dup2(fd0, 1);
    dup2(fd0, 2);
    close(fd0);

    /* Step5: make the daemon as session leader */
    setsid();

    /* Step6: set umask to 0 and its pwd to / */
    umask(0);
    chdir("/");


    (*daemon_job)(arg);
}

