#include "usr.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <directory_path>\n", argv[0]);
        exit(1);
    }

    char* directory_path = argv[1];
    traverse_directory(directory_path, 0);
    return 0;
}