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
