#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "util.h"

void fatal(const char *title) {
	perror(title);
	exit(errno);
}

ssize_t safe_getline(char ** lineptr, size_t * n, FILE * stream) {
	if (getline(lineptr, n, stream) < 0) {
		if (errno == 0) {
			fprintf(stderr, "getline: End of file\n");
			exit(1);
		}
		fatal("getline");
	}
}

ssize_t safe_read(int fd, void * buf, size_t n) {
	ssize_t ret;
	if ((ret = read(fd, buf, n)) <= 0)
		fatal("read");
	return ret;
}
