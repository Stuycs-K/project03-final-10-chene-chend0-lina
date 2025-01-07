#include "card.h"

// create individual card
struct card_node* createCard(int face, int suit, struct card_node *next){
    struct card_node *newCard = (struct card_node*)malloc(sizeof(struct card_node));
    newCard->face = face;
    newCard->suit = suit;
    newCard->next = next;
    return newCard;
}

// create a new deck of cards
void createDeck(struct card_node *deck){
    struct card_node *current = deck;
    for (int suit = 0; suit < NUM_SUITS; suit++){
        for (int face = 0; face < NUM_FACES; face++){
            struct card_node *newCard = createCard(face, suit, NULL);
            if (current == NULL){
                deck = newCard;
                current = deck;
            }
            else {
                current->next = newCard;
                current = newCard;
            }
        }
    }
}

void printCard(struct card_node *card){
    if (card){
        printf("%s of %s\n",faces[card->face],suits[card->face]);
    }
}

void printDeck(struct card_node *card){
    struct card_node *current = deck;
    while (current){
        printCard(current);
        current = current->next;
    }
}