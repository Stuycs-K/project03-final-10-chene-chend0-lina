#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> 
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h> 

void create_file() {
    int log_file = open("player_log.dat", O_WRONLY);
    close(log_file);
}

void write_file(char * data) {
    int log_file = open("player_log.dat", O_WRONLY | O_APPEND);
    if (write(log_file, data, sizeof(data)) == -1) {
        perror("Write to log file failed");
    }
    close(log_file);
    

}

void read_file() {

}