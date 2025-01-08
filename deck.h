#ifndef DECK_H
#define DECK_H

#define NUM_DECKS 4

#include "card.h"

struct card_node ** init(int NUM_DECKS); // 4 decks
void shuffle (struct card_node ** deck);
struct card_node * drawCard(struct card_node **deck);

#endif
