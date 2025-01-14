#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <errno.h>
#include "card.h"
#include "deck.h"
#include "server.h"
#include "networking.h"
#include <signal.h>
#include "log.h"
#include "sigs.h"
#include <errno.h>
#include "util.h"
#define KEY 102934

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

static int to_client_fd;

static void sigint_handler(int sig) {
    printf("Exiting game server.\n");
    remove(WKP);
    int semd = semget(KEY, 1, 0);
    if (semd == -1) {
        perror("Failed to get semaphore");
        exit(1);
    }

    if (semctl(semd, IPC_RMID, 0) == -1) {
        perror("Failed to remove semaphore");
        exit(1);
    }
    exit(0);
}

static void sigalrm_handler(int sig) {
    int timeout_game_over = -20;
    write(to_client_fd, &timeout_game_over, sizeof(timeout_game_over));
    exit(0);
}

int main() {
	signal(SIGINT, sigint_handler);
	int to_client;
	int from_client;
	int semd;
	union semun s;
	create_file();
	semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (semd == -1) {
		if (errno == EEXIST) {
			semd = semget(KEY, 1, 0);
			if (semd != -1) {
				semctl(semd, 0, IPC_RMID);
			}
			semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
			if (semd == -1) {
				perror("Failed to recreate semaphore");
				return 1;
			}
		}
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
			int check_server = 0;
			server_handshake(&to_client, from_client, &client_pid);
			if (write(to_client, &check_server, sizeof(check_server)) == -1) {
				perror("NO-OP failed");
				break;
			}
			char name[50];
			safe_read(from_client, name, sizeof(name));
			while(1) {
				play(to_client, from_client, char * name);
			}
		}
		else if (pid > 0) {
			close(from_client);
		}
		else {
			perror("forking subserver error");
			exit(1);
		}
	}
}

void send_card(int to_client, struct card_node *current) {
	const int player_turn = -10;
	if (write(to_client, &player_turn, sizeof(player_turn)) == -1) {
		perror("error sending player header");
		exit(1);
	}
	if (write(to_client, current, sizeof(struct card_node)) == -1) {
		perror("error sending player card:");
		printCard(current);
		exit(1);
	}
}

void play(int to_client, int from_client, char * name) {
	to_client_fd = to_client;
	signal(SIGALRM, sigalrm_handler);
	int card_value = 0;
	int game_over = 0;
	struct deck * _deck = initDeck(1);
	//shuffle card
	struct card_node * dealer_hand = NULL;
	struct card_node * player_hand = NULL;
	struct card_node * current = dealRandomCard(_deck); 
	addCardToHand(&dealer_hand, current);
	int dealer_turn = -11;
	int player_turn = -10;
	int make_move = -12;
	int win_round = -13;
	int lose_round = -14;
	int tie_round = -15;
	int player_blackjack = 0;
	int dealer_blackjack = 0;
	if (write(to_client, &dealer_turn, sizeof(dealer_turn) ) == -1) {
		perror("error writing dealer header");
		exit(1);
	} // knows to read dealer's card;
	if (write(to_client, current, sizeof(struct card_node)) == -1) {
		perror("error sending player face up card");
	}
	
	struct card_node * dealer_second = dealRandomCard(_deck); // keep track second card
	addCardToHand(&dealer_hand, dealer_second); //dealers second card
	current = dealRandomCard(_deck);
	addCardToHand(&player_hand, current);
	if (write(to_client, &player_turn, sizeof(player_turn)) == -1) {
		perror("error sending player header");
		exit(1);
	} // know to read client's cards;
	if (write(to_client, current, sizeof(struct card_node)) == -1) { // sends player first card;
		perror("error sending player first card");
		exit(1);
	}
	if (write(to_client, &player_turn, sizeof(player_turn)) == -1) {
		perror("error sending player header");
		exit(1);
	}
	current = dealRandomCard(_deck);
	addCardToHand(&player_hand, current);
	if (write(to_client, current, sizeof(struct card_node)) == -1) { // sends player second card;
		perror("error sending player second card");
		exit(1);
	}
	int dealer_total = calcHand(dealer_hand);
	int player_total = calcHand(player_hand);
	if (dealer_total == 21) {
		dealer_blackjack = 1;
	}
	if (player_total == 21) { // have to figure out a way to account for player suit blackjack;
		player_blackjack = 1;
	}
	else if (!dealer_blackjack) {
		current = dealRandomCard(_deck);
		while (current != NULL && !game_over) {
			if (player_total > 21) {
				game_over = 1;
				break;
			}
			
			if (write(to_client, &make_move, sizeof(make_move)) == -1) {
				perror("error sending player move header");
			} // client knows to make move

			/*
			if (write(to_client, current, sizeof(struct card_node)) == -1) {
				perror("error writing card to deck\n");
				exit(1);
			}
			*/
			alarm(30);
			char move;
			if (read(from_client, &move, sizeof(move)) <= 0) {
				perror("error reading player move to subserver\n");
				break;
			}
			alarm(0);
			if (move == 'h') {
				addCardToHand(&player_hand, current);
				player_total = calcHand(player_hand);
				send_card(to_client, current);
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
			current = dealRandomCard(_deck);
		}
	}
	if (write(to_client, &dealer_turn, sizeof(dealer_turn) ) == -1) {
		perror("error writing dealer header");
		exit(1);
	}  //get ready to read dealers second card
	
	if (write(to_client, dealer_second, sizeof(struct card_node)) == -1) {
		perror("error writing dealer's second card");
		exit(1);
	} // dealers second card;
	if (game_over) {
		if (write(to_client, &lose_round, sizeof(lose_round)) == -1) {
			perror("error writing lose round");
			exit(1);
		}
		return;
	}

	if (!(player_blackjack || dealer_blackjack)) {
		current = dealRandomCard(_deck);
		while (dealer_total < 17 && dealer_total <= player_total && current != NULL) {
			addCardToHand(&dealer_hand, current);
			if (write(to_client, &dealer_turn, sizeof(dealer_turn) ) == -1) {
				perror("error writing dealer header");
				exit(1);
			} // let client know to read card for dealer;
			if (write(to_client, current, sizeof(struct card_node)) == -1) {
				perror("error writing dealer card");
				exit(1);
			}
			dealer_total = calcHand(dealer_hand);
			current = dealRandomCard(_deck);
		}
	}
	// results
	if (dealer_total > 21) {
		if (write(to_client, &win_round, sizeof(win_round)) == -1) {
			perror("error writing win to client");
			exit(0);
		}
		return;
	}
	if (player_total > dealer_total) {
		if (write(to_client, &win_round, sizeof(win_round)) == -1) {
			perror("error writing win to client");
			exit(0);
		}
		return;
	}
	if (dealer_total > player_total) {
		if (write(to_client, &lose_round, sizeof(lose_round)) == -1) {
			perror("error writing lose round");
			exit(1);
		}
		return;
	}
	if (!player_blackjack && !dealer_blackjack && dealer_total == player_total) {
		if (write(to_client, &tie_round, sizeof(tie_round)) == -1) {
			perror("error writing tie round");
		}
		return;
	}
	if (!player_blackjack && dealer_blackjack) {
		if (write(to_client, &lose_round, sizeof(lose_round)) == -1) {
			perror("error writing lose round");
			exit(1);
		}
		return;
	}
	if (player_blackjack && !dealer_blackjack) {
		if (write(to_client, &win_round, sizeof(win_round)) == -1) {
			perror("error writing win to client");
			exit(0);
		}
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
