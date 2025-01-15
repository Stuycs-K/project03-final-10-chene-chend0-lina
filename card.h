#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define NUM_SUITS 4
#define NUM_FACES 13

// card structure
struct card_node{
    int face;
    int suit;
    struct card_node *next;
};

// faces array
static const char *faces[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

// suits array
static const char *suits[] = {"♥", "♦", "♣", "♠"};

// card management
struct card_node* createCard(int face, int suit, struct card_node *next);
struct card_node * append_card(struct card_node * original, struct card_node * end);
void freeCard(struct card_node *card);
void printCard(struct card_node *card);

// hand management
void addCardToHand(struct card_node **hand, struct card_node *card);
int calcHand(struct card_node *hand);
void printHand(struct card_node *hand);
void printHandAscii(struct card_node *hand);
void freeHand(struct card_node *hand);
void printTable(struct card_node *dealer_hand, struct card_node *player_hand, int reveal_dealer);

// blackjack specific
int isBlackjack(struct card_node *hand);
int isBust(struct card_node *hand);

#endif
