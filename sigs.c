#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "sigs.h"


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

void sigint_handler(int sig) {
    printf("Exiting game.")
    exit(0);
}

void sigalrm_handler(int sig) {
    printf("You didn't make a move and have been kicked!");
    exit(0);
}