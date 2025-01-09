#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
struct card_node* createCard(int face, int suit, struct card_node *next);
void freeCard(struct card_node *card);

// hand management
int calcHand(struct card_node *hand); // inc ace
void addCardToHand(struct card_node **hand, struct card_node *card);
void printHand(struct card_node *hand);
void freeHand(struct card_node *hand);

// utility
void printCard(struct card_node *card);

// struct card_node* insert(struct card_node *deck, int face, int suit);
// struct card_node * remove_card(struct card_node *deck, int face, int suit);


// include add random number of decks function

#endif
