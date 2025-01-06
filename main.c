#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void client() {
	printf("Clienting yes");
}
void server() {
	printf("Servering yes");
}
int main(void) {
	int child_pid;
	switch(child_pid = fork()) {
		case 0:
			client();
			return 0;
		case -1:
			perror("fork");
			return errno;
		default:
			server();
			return 0;
	}
}
