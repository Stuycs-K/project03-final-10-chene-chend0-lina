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
#include "log.h"

void create_file() {
    int log_file = open("player_log.dat", O_WRONLY);
    close(log_file);
}

void write_file(char * name, char * card, char move, int winnings ) {
    struct player_moves curr;
    strcpy(curr.name, name);
    strcpy(curr.card, card);
    curr.move = move;
    curr.winning = winnings;
    FILE *player_log = fopen("player_log.dat", "a+");
    if (fwrite(&player_log, sizeof(struct player_moves), 1, player_log) == -1) {
        perror("Write to log file failed");
    }
    fclose(player_log);
    

}

void read_file() {

}