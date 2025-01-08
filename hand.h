#ifndef HAND_H
#define HAND_H

#define NUM_DECKS 4

#include "card.h"

// hand structure
struct hand{
    struct card_node *cards;
    int score;
};

struct hand * createHand();
void addTohand(struct hand *hand, struct card_node *card);
int calcHand(struct hand *hand);
void printHand(struct hand *hand);
void freeHand(struct hand *hand);

#endif
