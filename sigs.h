#ifndef SIGS_H
#define SIGS_H

void setup_sighandler();
extern int to_client_fd; 
void sigalrm_handler(int sig);
#define TIME_LIMIT 30 //seconds

#endif