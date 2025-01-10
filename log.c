#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> 
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h> 
#include "log.h"

void create_file() {
    int log_file = open("player_log.dat", O_WRONLY | O_CREAT);
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
    struct stat buff;
    if (stat("player_log.dat, &buff") == -1) err();
    off_t file_size = buff.st_size;
    int num = file_size / sizeof(struct player_moves);
    struct player_moves data[num];
    int player_log_dat = open("./player_log.dat", O_RDONLY, 0);
    for (int i = 0; i < num; i++) {
        if (read(player_log_dat, &data[i], sizeof(struct player_moves)) == -1) err();
        printf("Player: %s\n", data[i].name);
        printf("Card: %s\n", data[i].card);
        printf("Move: %c\n", data[i].move);
        printf("Winnings: %d\n\n", data[i].winning);
    }
    close(player_log_dat);
}
