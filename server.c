#include <stdio.h>
#include "server.h"

void server(int in, int out) {
	FILE *in = fdopen(in, "r");
	FILE *out = fdopen(out, "w");
	printf("Servering yes %d %d\n", in, out);	
}
