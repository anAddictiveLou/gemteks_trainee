/**
 * @file user.h
 * @brief Header file containing function declarations for directory traversal.
 */

#ifndef _USER_H
#define _USER_H

#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Check if a directory is valid and can be opened.
 *
 * This function checks if the specified directory exists and can be opened.
 *
 * @param dir_name The name of the directory to check.
 * @return 1 if the directory is valid and can be opened, 0 otherwise.
 */
int directory_valid_check(char* dir_name);

/**
 * @brief Search for a file in a directory and its subdirectories.
 *
 * This function searches for a file with the specified name in the given directory
 * and its subdirectories. It returns the path to the first occurrence of the file found.
 *
 * @param directory_name The name of the directory to start the search from.
 * @param file_name The name of the file to search for.
 * @return The path to the first occurrence of the file found, or NULL if not found.
 */
char* search_in_directory(char* directory_name, char* file_name);

#endif
