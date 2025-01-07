#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define TIME_LIMIT 30 //seconds

void setup_kick_sighandler() {
    struct sigaction timeout;
    timeout.sa_handler = sigalrm_handler;
    timeout.sa_flags = 0;
    sigemptyset(&timeout.sa_mask);
    sigaction(SIGALRM, &timeout, NULL);
}
