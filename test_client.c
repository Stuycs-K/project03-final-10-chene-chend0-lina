#include <fcntl.h>
#include <unistd.h>
#include "client.h"
#include "card.h"
#include "util.h"


void write_stuff() {
	FILE * output = fopen("/tmp/buffer", "w");
	int buf = -10;
	fwrite(&buf, sizeof(int), 1, output);
	struct card_node* card = createCard(0, 1, NULL);
	fwrite(card, sizeof(struct card_node), 1, output);

	buf = -10;
	fwrite(&buf, sizeof(int), 1, output);
	struct card_node* card1 = createCard(10, 2, NULL);
	fwrite(card1, sizeof(struct card_node), 1, output);

	buf = -11;
	fwrite(&buf, sizeof(int), 1, output);
	struct card_node* card2 = createCard(11, 0, NULL);
	fwrite(card2, sizeof(struct card_node), 1, output);

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
