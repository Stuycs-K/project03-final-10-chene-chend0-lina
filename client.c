#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "card.h"
#include "client.h"
#include "log.h"
#include "networking.h"
#include "sigs.h"
#include "util.h"

void displayIntro() {
	printf("\n\n****\nBlackjack\n\nTry to get a score of 21, but no higher!\nFace cards are worth 10 points, and the Ace is worth 1 or 11 depending on what benefits you.\nHit to draw a new card, Stand to let the dealer draw.\n****\n\n");
}

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

// ========
// fetch relevant datatypes from the server
int fetch_int(int in) {
	int ret;
	safe_read(in, &ret, sizeof(int));
	return ret;
}

// WARNING: mallocs a buffer for the card
struct card_node * fetch_card(int in) {
	struct card_node * ret = malloc(sizeof(struct card_node));
	safe_read(in, ret, sizeof(struct card_node));
	ret->next = NULL;  // should not dereference arbitrary pointers!
	return ret;
}
// ========

void endResults(struct card_node *dealer_hand, struct card_node *player_hand){
	int dealer_score = calcHand(dealer_hand);
	int player_score = calcHand(player_hand);

	printf("\n=== END RESULTS ===\n");
	printf("\n Dealer's Score: %d\n",dealer_score);
	printHandAscii(dealer_hand);
	printf("\n Player's Score: %d\n",player_score);
	printHandAscii(player_hand);
	
	if (isBust(player_hand)){
		printf("\nYou busted! Dealer wins.\n");
	}
	else if (dealer_score > 21 || player_score > dealer_score){
		printf("\nYou win!\n");
	}
	else if (dealer_score > player_score){
		printf("\nDealer wins!\n");
	}
	else {
		printf("\nDraw!\n");
	}

}

enum Move read_move() {  // from stdin
	enum Move ret = NO_MOVE;
	char * ptr;
	size_t size;
	while (ret == NO_MOVE) {
		printf("(H)it or (S)tand: ");
		fflush(stdout);
		ptr = NULL;
		safe_getline(&ptr, &size, stdin);
		switch (ptr[0]) {
			// allow aliases for case-insensitivity/intuitive features
			case 'H':
			case 'h':
			case '1':
				ret = HIT;
				break;
			case 'S':
			case 's':
			case '2':
				ret = STAND;
				break;
			default:
				printf("Invalid input!\n");
		}
		free(ptr);
	}
	return ret;
}

void send_move(enum Move m, int out) {  // to server
	char buf = '\0';
	switch(m) {
		// map moves to server-side chars
		case HIT:
			buf = 'h';
			break;
		case STAND:
			buf = 's';
			break;
	}
	safe_write(out, &buf, sizeof(buf));
}

// implementation of core gameplay loop
void play(int in, int out) {
	// char as temporary type
	struct card_node *player_hand = NULL;
	struct card_node *dealer_hand = NULL;

	// booleans
	char active = 1;
	int reveal_dealer = 0;

	int buf = 21;
	// start game
	safe_write(out, &buf, sizeof(buf));
	// display
	while (active) {
		switch(buf = fetch_int(in)) {
			case 0:  // no-op, used for heartbeat pings
				break;
			case -10:  // read player card
				player_hand = append_card(player_hand, fetch_card(in));
				break;
			case -11:  // read dealer card
				dealer_hand = append_card(dealer_hand, fetch_card(in));
				break;
			case -12:  // send player move
				reveal_dealer = 1;
				printTable(dealer_hand, player_hand,reveal_dealer);
				send_move(read_move(), out);
				break;
			// win/lose/tie cases
			case -13:
			case -14:
			case -15:
				active = 0;
				printTable(dealer_hand, player_hand,reveal_dealer);
				endResults(dealer_hand, player_hand);
				break;
			default:
				fprintf(stderr, "WARNING: UNKNOWN COMMAND ID %d (%x)\n", buf, buf);
		}
	}
	freeHand(player_hand);
	freeHand(dealer_hand);
}

// WARNING: mallocs a buffer (>= 50 chars, as it can be realloc()d by getline())
void setName(int out) {
	char *name = malloc(50*(sizeof(char)));
	size_t size;
	printf("\nEnter your name: ");
	fflush(stdout);
	if (safe_getline(&name, &size, stdin) > 50)
		printf("Warning: truncating name for display...");
	name[49] = '\0';
	name = strsep(&name, "\r\n");
	safe_write(out, name, 50*(sizeof(char)));
	free(name);
}

void client(int in, int out) {
	signal(SIGINT, sigint_client);
	displayIntro();
	setName(out);
	while (1) {
		switch (readMainMenu()) {
			case PLAY:
				play(in, out);
				break;
			case LOGS:
				read_file();
				break;
			case QUIT:
				return;
		}
	}
}

int main(void) {
	int out = -1;
	// "online-only DRM"
	printf("Connecting to server...\n");
	int in = client_handshake(&out);
	client(in, out);
}
