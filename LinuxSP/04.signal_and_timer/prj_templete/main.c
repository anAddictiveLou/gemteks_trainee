#include "usr.h"

int main(int argc, char** argv)
{
    if (argc != 5)
    {
        printf("Usage: %s <file_name> <directory_path> <hard_link_file_name> <soft_link_file_name>\n", argv[0]);
        exit(1);
    }

    char* file_name = argv[1];
    char* directory_path = argv[2];
    char* hard_link_file_name = argv[3];
    char* soft_link_file_name = argv[4];

    if (directory_valid_check(directory_path) < 0)
    {   
        printf("Invalid directory\n");
        exit(1);
    }

    char* file_pos = NULL;
    if ( (file_pos = search_in_directory(directory_path, file_name)) != NULL)
    {
        printf("%s\n", file_pos);
        if (link(file_pos, hard_link_file_name) < 0)
        {
            printf("Create hard-link unsuccessfully\n");
        }
        else
        {
            printf("Create hard-link successfully\n");
        }
        
        if (symlink(file_pos, soft_link_file_name) < 0)
        {
            printf("Create symlink unsuccessfully\n");
        }
        else
        {
            printf("Create sym-link successfully\n");
        }
    }
    return 0;
}