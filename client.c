#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "card.h"
#include "client.h"
#include "util.h"

void displayIntro() {
	printf("\n\n****\nWIP\n****\n\n");
}

enum Action {
	NONE,
	PLAY,
	LOGS,
	QUIT
};

enum Action readMainMenu() {
	char *ptr = NULL;
	size_t size;
	enum Action ret = NONE;
	while (ret == NONE) {
		printf("\n\n(1) Play\t(2) View logs\t(3) Quit: ");
		fflush(stdout);
		ptr = NULL;
		safe_getline(&ptr, &size, stdin);
		switch (ptr[0]) {
			case '1':
				ret = PLAY;
				break;
			case '2':
				ret = LOGS;
				break;
			case '3':
				ret = QUIT;
				break;
			default:
				printf("Invalid input!\n");
		}
		free(ptr);
	}
	return ret;
}

void print_hand(const char *name, struct card_node *card) {
	printf("%s:\n", name);
	printDeck(card);
	printf("=====\n");
}

int fetch(struct card_node **p_hand, struct card_node **d_hand, int *winner) {
	// reads game state from server side
	// returns 1 when is player's turn
	// winner is 0 for no winner, -1 for dealer, 1 for player 1
	return 1;
}

enum Move read_move() {
	// reads move
	enum Move ret = NO_MOVE;
	char * ptr;
	size_t size;
	while (ret == NO_MOVE) {
		printf("(H)it or (S)tand: ");
		fflush(stdout);
		ptr = NULL;
		safe_getline(&ptr, &size, stdin);
		switch (ptr[0]) {
			case 'H':
			case 'h':
				ret = HIT;
				break;
			case 'S':
			case 's':
				ret = STAND;
				break;
			default:
				printf("Invalid input!\n");
		}
		free(ptr);
	}
	return HIT;
}
void send_move(enum Move m) {
	// sends move data to server side
}

void play() {
	// char as temporary type
	struct card_node *player_hand = createCard(0, 0, NULL);
	struct card_node *dealer_hand = createCard(0, 0, player_hand);
	int winner = 0;
	// display
	while (!winner) {
		print_hand("Dealer", dealer_hand);
		print_hand("Player", player_hand);
		if (fetch(&player_hand, &dealer_hand, &winner) == 1)
			send_move(read_move());
	}
}

void logs() {
	printf("<effectively cats the results file... tempted to actually just cat it>\n");
}

void client(int in_fd, int out_fd) {
	/*
	FILE *in = fdopen(in_fd, "r");
	FILE *out = fdopen(out_fd, "w");
	*/
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
