#include <fcntl.h>
#include <unistd.h>
#include "client.h"
#include "card.h"
#include "util.h"


void write_stuff() {
	FILE * output = fopen("/tmp/buffer", "w");
	int buf = -10;
	fwrite(&buf, sizeof(int), 1, output);
	struct card_node* card = createCard(0, 0, NULL);
	fwrite(card, sizeof(struct card_node), 1, output);
	buf = -12;
	fwrite(&buf, sizeof(int), 1, output);
	buf = -13;
	fwrite(&buf, sizeof(int), 1, output);
	fclose(output);
}

int main(void) {
	write_stuff();
	int in = open("/tmp/buffer", O_RDONLY);
	client(in, STDOUT_FILENO);
}
