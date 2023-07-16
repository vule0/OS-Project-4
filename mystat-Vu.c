#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>

// determines corresponding permission
char getPermissions(int stmode, int flag, char perm){
    if (stmode & flag){
        return perm;
    }
    else{
        return '-';
    }
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Invalid arguments\n");
        return 0;
    }   

    // uses stat syscall to display file information
    struct stat info;
    stat(argv[1], &info);
    printf("File Information of: %s\n", argv[1]);
    printf("File Size: %d bytes\n", info.st_size);
    printf("Number of Blocks Allocated: %ld\n", info.st_blocks);
    printf("Number of Links: %d\n", info.st_nlink);
    printf("File Permissions: ");
    // displaying permissions by comparing st_mode and permission flags
    // there are flags for owners, group, and others
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

    return 1;
}

