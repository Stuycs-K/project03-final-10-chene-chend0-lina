#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DECK_SIZE 52
#define NUM_SUITS 4
#define NUM_FACES 13

// card structure
struct card_node{
    int face;
    int suit;
    struct card_node *next;
};

// faces array
char *faces[] = {"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};

// suits array
char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};

// card management
void createDeck(struct card_node *deck);
struct card_node* createCard(int face, int suit, struct card_node *next);
void printCard(struct card_node *card);
void printDeck(struct card_node *deck);
struct card_node* insert(struct card_node *deck, int face, int suit);
struct card_node * random_card(struct card_node *deck);
struct card_node * remove_card(struct card_node *deck, int face, int suit);
void free_node(struct card_node *card);
struct card_node * free_list(struct card_node *deck);

// include ace function when calculating hand
int calcHand(struct card_node *deck);

// struct hand * createHand();
// void addTohand(struct hand *hand, struct card_node *card);
// int calcHand(struct hand *hand);
// void printHand(struct hand *hand);
// void freeHand(struct hand *hand);


// include add random number of decks function

#endif
