#ifndef DECK_H
#define DECK_H

#define DECK_SIZE 52
#define NUM_DECKS 4

#include "card.h"

struct deck{
    struct card_node *cards;
    int size; // num cards curr in deck
};

// deck func
struct deck * initDeck(int numDecks);
struct card_node * dealRandomCard(struct deck * deck);
void freeDeck(struct deck * deck);

// utility func
void printDeck(struct deck * deck);
void addDecks(struct deck *deck, int numDecks);

// void shuffleDeck(struct deck * deck);

#endif
