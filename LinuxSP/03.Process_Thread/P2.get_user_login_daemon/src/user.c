#include "user.h"

void* daemon_handle(void* arg)
{
    int fd = open(LOG_FILE_PATH, O_CREAT | O_APPEND | O_RDWR, 0666);
    if (fd = -1)
    {
        perror("open log file failed\n");
        exit(EXIT_FAILURE);
    }

    /* This code is reference to huyhu123 */
    while (1)
    {
        struct utmp *ut;
        setutent();
        while ((ut = getutent()) != NULL)
        {
            if (ut->ut_type == USER_PROCESS)
            {
                struct passwd *pw = getpwnam(ut->ut_user);
                if (pw != NULL)
                {
                    time_t now = time(NULL);
                    char *timestamp = ctime(&now);
                    timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline character
                    dprintf(fd, "%s: User %s logged at\n", timestamp, pw->pw_name);
                }
            }
        }
        endutent();
        sleep(60); 
    }

    close(fd);
    exit(EXIT_SUCCESS);
}