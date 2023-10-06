/**
 * @file usr.h
 * @brief Header file for the usr module.
 */

#ifndef _USR_H
#define _USR_H

#define LOG_FILE_PATH "/home/lou/Gemtek-training/LinuxSP/03.Process_Thread/P2.get_user_login_daemon/login_log"

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
#include <time.h>
#include <utmp.h>

/**
 * @brief Entry point for the daemon handling function.
 *
 * This function serves as the entry point for the daemon handling thread.
 * It takes a single argument as a pointer to data that may be required
 * by the daemon during its execution.
 *
 * @param arg A pointer to data required by the daemon.
 * @return A pointer to the result of the daemon execution.
 */
void* daemon_handle(void* arg);

#endif
