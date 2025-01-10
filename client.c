#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

int fetch_int(int in) {
	int ret;
	safe_read(in, &ret, sizeof(int));
	return ret;
}

struct card_node * fetch_card(int in) {
	// WARNING: mallocs a buffer for the card
	struct card_node * ret = malloc(sizeof(struct card_node));
	safe_read(in, ret, sizeof(struct card_node));
	ret->next = NULL;  // should not dereference arbitrary pointers!
	return ret;
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
void send_move(enum Move m, int out) {
	char buf = '\0';
	switch(m) {
		case HIT:
			buf = 'h';
			break;
		case STAND:
			buf = 's';
			break;
	}
	safe_write(out, &buf, sizeof(buf));
}

// TODO: conference with card.c
struct card_node * append_card(struct card_node * original, struct card_node * end) {
	if (!original)
		return end;
	struct card_node *buf = original;
	while (buf->next)
		buf = original->next;
	buf->next = end;
	end->next = NULL;   // redundant but good to be safe
	return original;
}

void play(int in, int out) {
	// char as temporary type
	struct card_node *player_hand = NULL;
	struct card_node *dealer_hand = NULL;
	char active = 1;
	int buf;
	// display
	while (active) {
		switch(buf = fetch_int(in)) {
			case -10:
				player_hand = append_card(player_hand, fetch_card(in));
				break;
			case -11:
				dealer_hand = append_card(dealer_hand, fetch_card(in));
				break;
			case -12:
				printf("\n");
				print_hand("Dealer", dealer_hand);
				print_hand("Player", player_hand);
				send_move(read_move());
				break;
			case -13:
				active = 0;
				print_hand("Dealer", dealer_hand);
				print_hand("Player", player_hand);
				printf("You win!");
				break;
			case -14:
				active = 0;
				print_hand("Dealer", dealer_hand);
				print_hand("Player", player_hand);
				printf("You lose!");
				break;
			default:
				fprintf(stderr, "WARNING: UNKNOWN COMMAND ID %d (%x)\n", buf, buf);
		}
	}
	/* TODO
	free_list(player_hand);
	free_list(dealer_hand);
	*/
}

void logs() {
	printf("<effectively cats the results file... tempted to actually just cat it>\n");
}

void client(int in, int out) {
	displayIntro();
	while (1) {
		switch (readMainMenu()) {
			case PLAY:
				play(in, out);
				break;
			case LOGS:
				logs();
				break;
			case QUIT:
				return;
		}
	}
}
