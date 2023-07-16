#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Error! Invalid arguments.\n");
        return 0;
    }

    struct stat info;

    if (stat(argv[2], &info) == -1){
        printf("Error finding file! Try again\n");
        perror("stat");
        return 0;
    }

    // intialize variables for required number of lines, the file descriptor, our line_buffer for reading the file, and integer flags for reading the lines
    int lines = atoi(argv[1]);
    int file = open(argv[2], O_RDONLY);
    char line_buffer;
    int i, num_lines = 0, num_chars = 0, new_num_lines = 0;
    off_t pos = info.st_size;

    for (i = 0; i < info.st_size; i++){
        if (read(file, &line_buffer, 1) != -1){
            lseek(file, --pos, SEEK_SET); // iterate through file backwards
            if (line_buffer == '\n'){       // check if we reach the required # of lines, else: keep reading
                new_num_lines = ++num_lines;
                if (new_num_lines == lines){
                    break;
                }
                num_chars++;
            }
            else{
                num_chars++;
            }

        }
    }

    if (num_lines == lines){
        lseek(file, 2, SEEK_CUR); // offset = current location + offset bytes
    }
    else{
        lseek(file, 0, SEEK_SET); // offset = offset bytes
    }

    // intialize, get output array, and print it
    char* output = malloc(num_chars * sizeof(char));
    printf("These are the last %d lines of: %s:\n", lines, argv[2]);
    read(file, output, num_chars);
    for (i = 0; i < num_chars; i++){
        printf("%c", output[i]);
    }
    return 1;
}