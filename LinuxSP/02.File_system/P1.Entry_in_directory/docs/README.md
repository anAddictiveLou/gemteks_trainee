# Problem 1. Write a program that accepts a directory name from the user and prints all file names and their types from that directory.

Solution1: 
    Read content of directory file itself cotaining entries and traverse and call stat() with each entry found to retrieve information: types, ...
    
Solution2:
    Use C function working with directory: opendir(), readdir(), ...