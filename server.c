#include <stdio.h>
#include <string.h>
#include "server.h"

void open_log() {
	// probably match to file.h
}
void write_move(enum Move m) {
	// write
}
void write_result(const char * line) {
	// write "X won/lost"
}
void shuffle (char cards[]) {
	// conference with the cards functoinality

}

void send_state(char player_cards[], char dealer_cards[], int winner) {

}

enum Move read_move() {
	return HIT;
}
int calculate_state(char player_cards[], char dealer_cards[]) {
	return 0;
}

void server(int in_fd, int out_fd) {
	FILE *in = fdopen(in_fd, "r");
	FILE *out = fdopen(out_fd, "w");
	printf("Servering yes %d %d\n", in_fd, out_fd);
	// awaits INIT
	char **ptr = NULL;
	int len;
	do {
		free(ptr);
		ptr = NULL;
		getline(ptr, &len, in);
	} while (!strcmp(*ptr, "INIT"));
	// opens log file to prevent duplicate servers
	open_log();
	int winner = 0;
	char cards[52];
	shuffle(cards);
	char player_cards[10];
	char dealer_cards[10];
	int j = 0;
	for (int i = 0; i < 2; i++) {
		player_cards[i] = cards[j++];
		dealer_cards[i] = cards[j++];
	}
	enum Move m;
	while (!winner) {
		send_state(player_cards, dealer_cards, winner);
		switch (m = read_move()) {
			case HIT:
				break;
			case STAND:
				break;
		}
		write_move();
		winner = calculate_state(player_cards, dealer_cards);
	}
	write_result("somebody won probably");
	// releases semaphore
	close_log();
}
