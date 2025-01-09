#include "deck.h"

struct deck *createDeck(){
    struct deck *deck = (struct deck*)malloc(sizeof(struct deck));
    deck->cards = NULL;
    deck->size = 0;

    for (int suit = 0; suit < NUM_SUITS; suit++){
        for (int face = 0; face < NUM_FACES; face++){
            struct card_node *newCard = createCard(face, suit, deck->cards);
            deck->cards = newCard;
            deck->size++;
        }
    }
    // need to implement shufle
    return deck;
}

void shuffleDeck(struct deck * deck);

struct card_node * dealCard(struct deck * deck){
    if (!deck || !deck->cards) return NULL;
    struct card_node *top = deck->cards;
    deck->cards = top->next;
    top->next = NULL;
    deck->size = deck->size - 1;
    return top;
}

void freeDeck(struct deck * deck){
    if (!deck) return;
    freeHand(deck->cards);
    free(deck);
}

void printDeck(struct deck * deck){
    if (!deck){
        printf("Empty Deck\n");
        return;
    }
    printf("Deck has %d cards:\n", deck->size);
    struct card_node *current = deck->cards;
    while (current){
        printf("%s of %s\n",faces[current->face],suits[current->suit]);
        current = current->next;
    }
}