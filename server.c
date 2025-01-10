#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "card.h"
#include "deck.h"
#include "server.h"
#include "networking.h"
#include "log.h"
#include "sigs.h"
#define KEY 102934

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};
int main() {
	int to_client;
	int from_client;
	int semd;
	union semun s;

	semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (semd == -1) {
		perror("Failed to create semaphore");
		return 1;
	}
	s.val = 1;
	if (semctl(semd, 0, SETVAL, s) == -1) {
		perror("Failed to set semaphore value to 1");
		return 1;
	}
	while (1) {
		from_client = server_setup();
		int pid = fork();
		if (pid == 0) {
			int to_client;
			int client_pid;
			server_handshake(&to_client, from_client, &client_pid);
			while(1) {
				play(to_client, from_client);
			}
		}
		if (pid > 0) {
			close(from_client);
		}
		else {
			perror("forking subserver error");
		}
	}
}

void play(int to_client, int from_client) {
	/*
	char client_pipe[20];
	sprintf(client_pipe, "%d", client_pid);
	strcat(client_pipe, "_fd");
	*/
	int card_value = 0;
	int game_over = 0;
	struct deck * _deck = initDeck(1);
	//shuffle card
	struct card_node * current = _deck->cards;
	int dealer_total = current->face;
	int dealer_turn = -11;
	int player_turn = -10;
	int make_move = -12;
	int win_round = -13;
	int lose_round = -14;
	int tie_round = -15;
	int player_blackjack;
	int dealer_blackjack;
	if (write(to_client, &dealer_turn, sizeof(dealer_turn) ) == -1) {
		perror("error writing dealer header");
	} // knows to read dealer's card;
	if (write(to_client, current, sizeof(struct card_node)) == -1) {
		perror("error sending player face up card");
	}
	current = current->next;
	struct card_node * dealer_second = current;
	dealer_total += current->face; //dealers second card
	current = current->next;
	int player_total = current->face;
	write(to_client, &player_turn, sizeof(player_turn)); // know to read client's cards;
	if (write(to_client, current, sizeof(struct card_node)) == -1) { // sends player first card;
		perror("error sending player first card");
	}
	write(to_client, &player_turn, sizeof(player_turn));
	current = current->next;
	player_total += current->face;
	if (write(to_client, current, sizeof(struct card_node)) == -1) { // sends player second card;
		perror("error sending player second card");
	}
	if (dealer_total == 21) {
		dealer_blackjack = 1;
	}
	current = current->next;
	if (player_total == 21) { // have to figure out a way to account for player suit blackjack;
		player_blackjack = 1;
	}
	else { 
		while (current != NULL && !game_over) {
		
		if (player_total > 21) {
			// printf("You've bust! Turn over\n");
			game_over = 1;
			
			break;
		}
		
		write(to_client, &make_move, sizeof(make_move)); // client knows to read card and make move

		if (write(to_client, current, sizeof(struct card_node)) == -1) {
			perror("error writing card to deck\n");
			exit(1);
		}

		char move;
		if (read(from_client, &move, sizeof(move) <= 0)) {
			perror("error reading player move to subserver\n");
		}
		if (move == 'h') {
			player_total += current->face;
			
		}
		else if (move == 's') {
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
	}
	
	if (game_over) {
		write(to_client, &lose_round, sizeof(lose_round));
		return;
	}
	if (write(to_client, &dealer_turn, sizeof(dealer_turn) ) == -1) {
		perror("error writing dealer header");
	}  //get ready to read dealers second card
	write(to_client, dealer_second, sizeof(struct card_node)); // dealers second card;

	current = current->next;
	while (dealer_total < 17 && current != NULL) {
		dealer_total += current->face;
		if (write(to_client, &dealer_turn, sizeof(dealer_turn) ) == -1) {
			perror("error writing dealer header");
		} // let client know to read card for dealer;
		write(to_client, current, sizeof(struct card_node));
		current = current->next;
	}
	// results
	if (dealer_total > 21) {
		write(to_client, &win_round, sizeof(win_round));
		return;
	}
	if (player_total > dealer_total) {
		write(to_client, &win_round, sizeof(win_round));
		return;
	}
	if (dealer_total > player_total) {
		write(to_client, &lose_round, sizeof(lose_round));
		return;
	}
	if (!player_blackjack && !dealer_blackjack && dealer_total == player_total) {
		write(to_client, &tie_round, sizeof(tie_round));
		return;
	}
	if (!player_blackjack && dealer_blackjack) {
		write(to_client, &lose_round, sizeof(lose_round));
		return;
	}
	if (player_blackjack && !dealer_blackjack) {
		write(to_client, &win_round, sizeof(win_round));
		return;
	}
	if (player_blackjack && dealer_blackjack) {
		write(to_client, &tie_round, sizeof(tie_round));
		return;
	}
	return;
	
	//select card
	//send card to player
	

	//wait for play response
	//adds next player

}
