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

void print_file_name_with_depth(char* file_name, int depth)
{
    for (int i = 0; i < depth; i++)
        printf(" ");
    printf("%s\n", file_name);
}

void traverse_directory(char* directory_name, int depth)
{
    if (directory_valid_check(directory_name) < 0)
    {
        printf("this is not a directory path\n");
        exit(1);
    }
    DIR* dr = NULL;
    if ( NULL == (dr = opendir(directory_name)) )
    {
        perror("Failed to open dir.");
        exit(1);
    }
    struct dirent* dir_entry;
    while( NULL != (dir_entry = readdir(dr)) )
    {
        /* If entry is a diretory, call traverse_directory() with depth + 1 */
        if ( DT_DIR == dir_entry->d_type )
        {
            int cur_dir = strcmp(dir_entry->d_name, ".");
            int parent_dir = strcmp(dir_entry->d_name, "..");
            /* Traverse only if it is not current directory and parent directory */
            if ( (cur_dir != 0) && (parent_dir != 0))
            {
                print_file_name_with_depth(dir_entry->d_name, depth);
                char new_dir[PATH_MAX] = {0};
                strncpy(new_dir, directory_name, PATH_MAX);
                strncat(new_dir, "/", PATH_MAX);
                strncat(new_dir, dir_entry->d_name, PATH_MAX);
                traverse_directory(new_dir, depth+1);
            }
        }

        /* else print out name of file */
        else
        {
            print_file_name_with_depth(dir_entry->d_name, depth);
        }
    }
    closedir(dr);
}
