#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "client.h"
#include "server.h"
#include "util.h"

int main(void) {
	int child_pid;
	int server2client[2], client2server[2];
	if (pipe(server2client) || pipe(client2server))
		fatal("pipe");
	switch(child_pid = fork()) {
		case -1:
			fatal("fork");
		case 0:
			client(server2client[0], client2server[1]);
			return 0;
		default:
			server(client2server[0], server2client[1]);
			return 0;
	}
}
