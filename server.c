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
			while(1) {
				play();
			}
		}
	}
}

void play(int to_client, int client_pid) {
	char client_pipe[20];
	int card_value = 0;
	int game_over = 0;
	sprintf(client_pipe, "%d", client_pid);
	strcat(client_pipe, "_fd");
	int from_client = open(client_pipe, O_RDONLY);
	struct card_node * deck;
	createDeck(deck);
	//shuffle card
	struct card_node * current = deck;
	int dealer_total = current->face;
	int dealer_turn = -11;
	int player_turn = -10;
	int make_move = -12;
	write(to_client, &dealer_turn, sizeof(dealer_turn) ); // knows to read dealer's card;
	if (write(to_client, current, sizeof(current)) == -1) {
		perror("error sending player face up card");
	}
	current = current->next;
	struct card_node * dealer_second = current;
	dealer_total += current->face; //dealers second card
	current = current->next;
	int player_total = current->face;
	write(to_client, &player_turn, sizeof(player_turn)); // know to read client's cards;
	if (write(to_client, current, sizeof(current)) == -1) { // sends player first card;
		perror("error sending player first card");
	}
	write(to_client, &player_turn, sizeof(player_turn));
	current = current->next;
	player_total += current->face;
	if (write(to_client, current, sizeof(current)) == -1) { // sends player second card;
		perror("error sending player second card");
	}
	while (current != NULL && !game_over) {
		if (player_total > 21) {
			// printf("You've bust! Turn over\n");
			game_over = 1;
			
			break;
		}
		if (player_total == 21) {
			break;
		}
		write(to_client, )
		if (write(to_client, current, sizeof(card_node)) == -1) {
			perror("error writing card to deck\n");
			exit(1);
		}
		char move;
		
		if (read(from_client, &move, sizeof(move) <= 0)) {
			perror("error reading player move to subserver\n");
		}
		if (move == "h") {
			player_total += current->face;
			
		}
		else if (move == "s") {
			break;
		}
		if (player_total == 21) {
			break;
		}
		if (player_total > 21) {
			
			game_over = 1;
			
			break;
		}
		current = current->next;
	}
	write(to_client, &dealer_turn, sizeof(dealer_turn)); // client expects to read dealers second card;
	

	if (!game_over &&  )
	//select card
	//send card to player
	

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
