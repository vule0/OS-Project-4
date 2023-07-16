#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void recursive(char* path){
    struct dirent *directory;
    DIR *dir = opendir(path);
    char p[1000];

    printf("Current Path: %s\n====================================\n", path);
    //read current directory or specified directory (root)
    while ((directory = readdir(dir)) != NULL){
        if (strcmp(directory->d_name, "..") != 0 && strcmp(directory->d_name, ".") != 0){
            printf("File Name: %s\n", directory->d_name);
            // read current directory and recursively display subtrees if that directory exists
            struct stat temp;
            if (stat(directory->d_name, &temp) != -1){
                if (S_ISDIR(temp.st_mode)){
                    strcpy(p, path);
                    strcat(p, "/");
                    strcat(p, directory->d_name);
                    printf("====================================\n\n");
                    recursive(p);
                }
            }
        }
    }
    closedir(dir);
}

int main(int argc, char* argv[]){
    // read current directory
    if (argc == 1){
        char buff[1000];
        recursive(getcwd(buff, sizeof(buff)));
    }
    // read specified directory
    else if (argc == 2){
        recursive(argv[1]);
    }
    else{
        printf("Error! Invalid arguments\n");
        return 0;
    }
    printf("Search has finished!\n");
    return 1;
}