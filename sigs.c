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
        return 1;
    }


    if (semctl(semd, IPC_RMID, 0) == -1) {
        perror("Failed to remove semaphore");
        return 1;
    }
    exit(0);
}

static void sigalrm_handler(int sig) {
    printf("You didn't make a move and have been kicked!");
    exit(0);
}
