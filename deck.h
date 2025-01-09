#ifndef DECK_H
#define DECK_H

#define DECK_SIZE 52
#define NUM_DECKS 4

#include "card.h"

struct deck{
    struct card_node *cards;
    int size; // num cards curr in deck
};

struct deck * init(); // 4 decks
// void shuffleDeck(struct deck * deck);
struct card_node * dealRandomCard(struct deck * deck);
void freeDeck(struct deck * deck);

void printDeck(struct deck * deck);

#endif
