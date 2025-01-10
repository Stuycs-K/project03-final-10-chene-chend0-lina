#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "sigs.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 102934

extern int to_client_fd; 

static void sigint_handler(int sig) { // on client side
    printf("Exiting game.\n")
    semd = semget(KEY, 1, 0);
    if (semd == -1) {
        perror("Failed to get semaphore");
        exit(1);
    }


    if (semctl(semd, IPC_RMID, 0) == -1) {
        perror("Failed to remove semaphore");
        exit(1);
    }
    exit(0);
}

static void sigalrm_handler(int sig) {
    int timeout_game_over = -20;
    write(to_client_fd, &timeout_game_over, sizeof(timeout_game_over));
    exit(0);
}
