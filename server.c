#include <stdio.h>
#include <string.h>
#include "server.h"
#include "card.h"

int main() {
	int to_client;
	int from_client;
	while (1) {
		from_client = server_setup();
		int pid = fork();
		if (pid == 0) {
			int to_client;
			int client_pid;
			server_handshake(&to_client, from_client, &client_pid);
			play();
		}
	}
}

void play(int to_client, int client_pid) {
	char client_pipe[20];
	sprintf(client_pipe, "%d", client_pid);
	strcat(client_pipe, "_fd");
	int from_client = open(client_pipe, O_RDONLY);
	struct card_node * deck;
	createDeck(deck);
	//shuffle card
	struct card_node * current = deck;
	while (current != NULL) {
		if (write(to_client, current, sizeof(card_node)) == -1) {
			perror("error writing card to deck");
		}
	}
	//select card
	//send card to player
	
	open(to_client);
	write()
	//wait for play response
	//adds next player

}
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
