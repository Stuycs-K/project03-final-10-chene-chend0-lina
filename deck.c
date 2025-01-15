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

// WARNING: mallocs the deck struct and the corresponding linked-list of cards; be sure to freeDeck()
struct deck * initDeck(int numDecks){
    if (numDecks <= 0) return NULL;
    struct deck *deck = (struct deck*)malloc(sizeof(struct deck));
    deck->cards = NULL;
    deck->size = 0;

    addDecks(deck, numDecks);
    return deck;
}

// WARNING: dealt cards will NOT be free()d  in freeDeck(), it is recommended that ALL drawn cards be in a hand (card linked-list) that is freed
struct card_node * dealRandomCard(struct deck * deck){
    if (!deck || !deck->cards) return NULL;
    struct card_node * prev = NULL;
    struct card_node * temp = deck->cards;
    int end = rand() % deck->size;
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
    deck->size--;

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
