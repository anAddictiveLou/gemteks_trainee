/**
 * @file user.h
 * @brief Header file containing function declarations for directory traversal.
 */

#ifndef _DAEMON_H
#define _DAEMON_H

#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <pwd.h>


/**
 * @brief Create a daemon process.
 *
 * This function creates a daemon process by forking the current process and
 * performing various steps to detach it from the controlling terminal.
 *
 * @param daemon_job A pointer to the function that the daemon process should execute.
 * @param arg An argument to be passed to the `daemon_job` function.
 */
void create_daemon(void* (*daemon_job)(void*), void* arg);

#endif
