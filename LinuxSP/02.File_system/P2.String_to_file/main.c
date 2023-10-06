#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments are provided
    if (argc != 3) {
        printf("Usage: %s <filename> <string>\n", argv[0]);
        return 1;
    }

    // Get the filename and string from command-line arguments
    char *filename = argv[1];
    char *string = argv[2];

    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    // Write the string into the file
    if (fprintf(file, "%s\n", string) < 0) {
        perror("Error writing to the file");
        fclose(file);
        return 1;
    }

    // Close the file
    fclose(file);
    return 0;
}
