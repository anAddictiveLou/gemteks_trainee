#include "usr.h"

int directory_valid_check(char* dir_name)
{
    int ret = 0;
    struct stat* dir_metadata = (struct stat*) calloc(1, sizeof(struct stat));
    if ( (ret = stat(dir_name, dir_metadata)) < 0)
    {
        perror("Failed to retrieve metadata for directory.");
        exit(1);
    }

    if ((dir_metadata->st_mode & S_IFMT) != S_IFDIR)
    {
        printf("%s is not a directory.\n", dir_name);
        exit(1);
    }
    return ret;
}

char* search_in_directory(char* directory_name, char* file_name)
{
    DIR* dr = NULL;
    char* ret = NULL;
    if ( NULL == (dr = opendir(directory_name)) )
    {
        perror("Failed to open dir.");
        exit(1);
    }
    struct dirent* dir_entry;
    while( NULL != (dir_entry = readdir(dr)) )
    {
        if (ret != NULL)
            break;
        /* If entry is a diretory, call traverse_directory() with depth + 1 */
        if ( DT_DIR == dir_entry->d_type )
        {
            int cur_dir = strcmp(dir_entry->d_name, ".");
            int parent_dir = strcmp(dir_entry->d_name, "..");
            /* Traverse only if it is not current directory and parent directory */
            if ( (cur_dir != 0) && (parent_dir != 0))
            {
                char new_dir[PATH_MAX] = {0};
                strncpy(new_dir, directory_name, PATH_MAX - strlen(new_dir));
                strncat(new_dir, "/", PATH_MAX - strlen(new_dir));
                strncat(new_dir, dir_entry->d_name, PATH_MAX - strlen(new_dir));
                ret = search_in_directory(new_dir, file_name);
            }
        }

        else
        {
            if (strcmp(file_name, dir_entry->d_name) == 0)
            {
                printf("Found %s in %s\n", file_name, directory_name);
                char* file_path = (char*) calloc(PATH_MAX, sizeof(char));
                strncpy(file_path, directory_name, PATH_MAX - strlen(file_path));
                strncat(file_path, "/", PATH_MAX - strlen(file_path));
                strncat(file_path, dir_entry->d_name, PATH_MAX - strlen(file_path));
                return file_path;
            }
        }

    }
    closedir(dr);
    return ret;
}

