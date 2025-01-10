#ifndef SIGS_H
#define SIGS_H

void setup_sighandler();
// extern int to_client_fd;
static void sigalrm_handler(int sig);
static void sigint_handler(int sig);
void sigint_client(int sig);
#define TIME_LIMIT 30 //seconds

#endif
