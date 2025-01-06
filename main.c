#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void client(int in, int out) {
	printf("Clienting yes %d %d\n", in, out);
}
void server(int in, int out) {
	printf("Servering yes %d %d\n", in, out);
}

void fatal(const char *title) {
	perror(title);
	exit(errno);
}

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
