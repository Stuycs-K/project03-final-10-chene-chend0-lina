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
int client_handshake(int *to_server) {
  char private_pipe[256];
  sprintf(private_pipe, "%d", getpid());

  if (mkfifo(private_pipe, 0666) == -1) {
    perror("error creating private pipe");
    exit(1);
  }

  *to_server = open(WKP, O_WRONLY);
  if (*to_server == -1) {
    perror("error connecting to server");
    unlink(private_pipe);
    exit(1);
  }

  if (write(*to_server, private_pipe, sizeof(private_pipe)) == -1) {
    perror("error sending PP name");
    unlink(private_pipe);
    exit(1);
  }

  int private_fd = open(private_pipe, O_RDONLY);
  if (private_fd == -1) {
    perror("error opening PP");
    unlink(private_pipe);
    exit(1);
  }

  int server_num;
  if (read(private_fd, &server_num, sizeof(server_num)) <= 0) {
    perror("error reading from server");
    unlink(private_pipe);
    close(private_fd);
    exit(1);
  }

  int ack = server_num + 1;
  if (write(*to_server, &ack, sizeof(ack)) == -1) {
    perror("error sending ack to server");
    unlink(private_pipe);
    close(private_fd);
    exit(1);
  }
}