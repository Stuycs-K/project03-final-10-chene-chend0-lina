#ifndef NETWORKING_H
#define NETWORKING_H
int server_setup();
int server_handshake(int *to_client, int from_client, int * client_pid);
#endif