#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include "networking.h"
#define READ 0
#define WRITE 1

int server_setup() {
  if (mkfifo(WKP, 0666) == -1) {
    perror("error creating WKP");
    remove(WKP);
    exit(1);
  }
  int from_client = open(WKP, O_RDONLY);
  if (from_client == -1) {
    perror("error opening WKP");
    exit(1);
  }
  unlink(WKP);
  return from_client;
}

int server_handshake(int *to_client, int from_client) {
  char client_pipe[256];
  if (read(from_client, client_pipe, sizeof(client_pipe)) <= 0) {
    perror("error reading client pipe name");
    unlink(WKP);
    exit(1);
  }
 

  *to_client = open(client_pipe, O_WRONLY);
  if (*to_client == -1) {
    perror("error opening client pipe");
    exit(1);
  }
  srand(time(NULL));
  int random_num = rand() % 100000;
  if (write(*to_client, &random_num, sizeof(random_num)) == -1) {
    perror("error writing to client");
    exit(1);
  }

  int ack;
  if (read(from_client, &ack, sizeof(ack)) <= 0 || ack != random_num + 1) {
    perror("Handshake failed");
    close(*to_client);
    exit(1);
  }
}