#include <stdio.h>
#include "client.h"

void displayIntro() {
	printf("\n\n****\nWIP\n****\n\n");
}

enum Action {
	PLAY,
	LOGS,
	QUIT
};

enum Action readMainMenu() {
	char **ptr;
	int size;
	while (1) {
		printf("\n\n(1) Play\t(2) View logs\t(3) Quit: ");
		fflush(stdout);
		ptr = NULL;
		getline(ptr, &size, stdin);
		switch (*ptr[0]) {
			case '1':
				return PLAY;
			case '2':
				return LOGS;
			case '3':
				return QUIT;
			default:
				printf("Invalid input!\n");
				free(ptr);
		}
	}

}

void print_hand(const char *name, char cards[], size_t n) {
	printf("%s: ", name);
	for (size_t i = 0; i < n; i++)
		printf("%c ", cards[i]);
	printf("\n");
}

int fetch(char player_cards[], char dealer_cards[], int *winner) {
	// reads game state from server side
	// returns 1 when is player's turn
	// winner is 0 for no winner, -1 for dealer, 1 for player 1
}

enum Move {
	HIT,
	STAND
}
enum Move read_move() {
	// reads move
	return HIT;
}
void send_move(enum Move m) {
	// sends move data to server side
}

void play() {
	// char as temporary type
	char player_cards[3] = {'?', '?', '?'};
	char dealer_cards[3] = {'?', '?', '?'};
	int winner = 0;
	// display
	while (!winner) {
		print_hand("Dealer", dealer_cards, 2);
		print_hand("Player", player_cards, 2);
		if (fetch(player_cards, dealer_cards, &winner) == 1)
			send_move(read_move());
	}
}

void logs() {
	printf("<effectively cats the results file... tempted to actually just cat it>\n");
}

void client(int in, int out) {
	FILE *in = fdopen(in, "r");
	FILE *out = fdopen(out, "w");
	printf("Clienting yes %d %d\n", in, out);
	displayIntro();
	while (1) {
		switch (readMainMenu()) {
			case PLAY:
				play();
				break;
			case LOGS:
				logs();
				break;
			case QUIT:
				return;
		}
	}
}
