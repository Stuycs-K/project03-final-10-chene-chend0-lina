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
void setup_sighandler() {
    struct sigaction exit;
    exit.sa_handler = sigint_handler;
    exit.sa_flags = 0;
    sigemptyset(&exit.sa_mask);
    sigaction(SIGINT, &exit, NULL);
    struct sigaction timeout;
    timeout.sa_handler = sigalrm_handler;
    timeout.sa_flags = 0;
    sigemptyset(&timeout.sa_mask);
    sigaction(SIGALRM, &timeout, NULL);
}

static void sigint_handler(int sig) {
    printf("Exiting game.")
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
