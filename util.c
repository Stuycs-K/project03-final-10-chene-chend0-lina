#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "util.h"

void fatal(const char *title) {
	perror(title);
	exit(errno);
}

