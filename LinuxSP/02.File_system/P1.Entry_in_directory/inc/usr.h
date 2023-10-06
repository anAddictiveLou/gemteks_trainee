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

/**
 * @brief Check if a directory is valid and accessible.
 *
 * This function checks if a directory exists and is accessible.
 *
 * @param dir_name The name of the directory to check.
 * @return 1 if the directory is valid and accessible, 0 otherwise.
 */
int directory_valid_check(char* dir_name);

/**
 * @brief Print the name of a file with its depth in the directory tree.
 *
 * This function prints the name of a file along with its depth in the directory tree.
 *
 * @param file_name The name of the file to print.
 * @param depth The depth of the file in the directory tree.
 */
void print_file_name_with_depth(char* file_name, int depth);

/**
 * @brief Traverse a directory and its subdirectories.
 *
 * This function recursively traverses a directory and its subdirectories,
 * printing the names of files and directories.
 *
 * @param directory_name The name of the directory to start traversal from.
 * @param depth The current depth in the directory tree.
 */
void traverse_directory(char* directory_name, int depth);

#endif
