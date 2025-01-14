#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "sigs.h"
#include <sys/ipc.h>
#include <sys/sem.h>

void sigint_client(int sig) {
	if (sig != SIGINT) {
		fprintf(stderr, "Invalid signal #%d\n", sig);
		return;
	}
	printf("\nInterrupted, exiting game...");
	exit(0);
}
