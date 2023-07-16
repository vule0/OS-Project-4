#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>


char getPermissions(int stmode, int flag, char perm){
    if (stmode & flag){
        return perm;
    }
    else{
        return '-';
    }
}

// print stats for a given file
void print(struct stat info){
    
    printf("Owner ID: %d\n", info.st_uid);
    printf("Group ID: %d\n", info.st_gid);
    printf("File Size: %d bytes\n", info.st_size);
    printf("Number of Blocks Allocated: %ld\n", info.st_blocks);
    printf("Number of Links: %d\n", info.st_nlink);
    printf("File Permissions: ");
    printf((S_ISDIR(info.st_mode)) ? "d" : "-");

    printf("%c", getPermissions(info.st_mode, S_IRUSR, 'r'));
    printf("%c", getPermissions(info.st_mode, S_IWUSR, 'w'));
    printf("%c", getPermissions(info.st_mode, S_IXUSR, 'x'));

    printf("%c", getPermissions(info.st_mode, S_IRGRP, 'r'));
    printf("%c", getPermissions(info.st_mode, S_IWGRP, 'w'));
    printf("%c", getPermissions(info.st_mode, S_IXGRP, 'x'));

    printf("%c", getPermissions(info.st_mode, S_IROTH, 'r'));
    printf("%c", getPermissions(info.st_mode, S_IWOTH, 'w'));
    printf("%c", getPermissions(info.st_mode, S_IXOTH, 'x'));

    printf("\n");
    printf("File Inode: %ld\n", info.st_ino);
}


void printDetails(struct dirent *directory, DIR* dir, char* path, int showDetails){
    // display file stats for all files in directory
    if (showDetails){
        dir = opendir(path);
        while ((directory = readdir(dir)) != NULL){
            if (strcmp(directory->d_name, "..") != 0 && strcmp(directory->d_name, ".") != 0){
                printf("%s\n", directory->d_name);
                struct stat temp;
                stat(directory->d_name, &temp);
                print(temp);
                printf("==============================\n");
                }
        }
    }
    // display all files in directory
    else{
        dir = opendir(path);
        while ((directory = readdir(dir)) != NULL){
            if (strcmp(directory->d_name, "..") != 0 && strcmp(directory->d_name, ".") != 0){
                printf("%s\n", directory->d_name);
            }
        }
    }
}
int main(int argc, char* argv[]){
    struct stat file;
    struct dirent *directory;
    DIR* dir;

    // No other arguments: print all files
    if (argc == 1){
        printDetails(directory, dir, ".", 0);
    }

    // Two arguments: print all files in selected directory OR print all files and details in current directory
    else if (argc == 2){
        if (strcmp(argv[1], "-l") == 0){
            printDetails(directory, dir, ".", 1);
        }
        else{
            printDetails(directory, dir, argv[1], 0);
        }
    }
    // Three arguments: print all files AND details in a selected directory
    else if (argc == 3){
        // second command line arg is "l", we print all details and the selected directory from argv[2]
        if (strcmp(argv[1], "-l") == 0){
            printDetails(directory, dir, argv[2], 1);
        }
        // third command line arg is "l", we print all details and the selected directory from argv[1]
        else if (strcmp(argv[2], "-l") == 0){
            printDetails(directory, dir, argv[1], 1);
        }
        else{
            printf("Error! Invalid arguments.\n");
        }
    }

    else{
        printf("Error!. Invalid arguments.\n");
        return 0;
    }

    return 1;
}
