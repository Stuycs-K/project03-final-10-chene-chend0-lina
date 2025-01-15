#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "util.h"

// simple perror/exit wrapper
void fatal(const char *title) {
	if (errno)
		perror(title);
	exit(errno);
}


// wrappers around I/O functions with error checking
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

ssize_t safe_write(int fd, void * buf, size_t n) {
	ssize_t ret;
	if ((ret = write(fd, buf, n)) <= 0)
		fatal("write");
	return ret;
}
