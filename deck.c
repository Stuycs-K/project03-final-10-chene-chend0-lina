#include "deck.h"

void addDecks(struct deck *deck, int numDecks){
    if (!deck) return;
    for (int i = 0; i < numDecks; i++){
        for (int suit = 0; suit < NUM_SUITS; suit++){
            for (int face = 0; face < NUM_FACES; face++){
                struct card_node *newCard = createCard(face, suit, deck->cards);
                deck->cards = newCard;
                deck->size++;
            }
        }
    }
}

struct deck * initDeck(int numDecks){
    if (numDecks <= 0) return NULL;
    struct deck *deck = (struct deck*)malloc(sizeof(struct deck));
    deck->cards = NULL;
    deck->size = 0;

    addDecks(deck, numDecks);
    return deck;
}

// void shuffleDeck(struct deck * deck){
//     if (!deck || deck->size <= 1){
//         return;
//     }
//     struct card_node **cardArray = (struct card_node**)malloc(deck->size * sizeof(struct card_node *));
//     for (int i = 0; i < size-1; i++){
//         int j = i + rand() / ()
//     }
// }

struct card_node * dealRandomCard(struct deck * deck){
    if (!deck || !deck->cards) return NULL;
    // always has 52
    struct card_node * prev = NULL;
    struct card_node * temp = deck->cards;
    int end = rand() % DECK_SIZE;
    for (int i = 0; i < end; i++){
        prev = temp;
        temp = temp->next;
    }
    // removes from deck 
    if (prev){
        prev->next = temp->next;
    }
    else {
        deck->cards = temp->next;
    }

    temp->next = NULL;
    return temp;
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