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
    struct card_node * temp = deck->cards;
    int end = rand() % DECK_SIZE;
    for (int i = 0; i < end; i++){
        temp = temp->next;
    }
    // removes from deck 
    struct card_node

    temp->next = NULL;
    return temp;
}

// struct card_node * remove_card(struct card_node *deck, int face, int suit){
//   struct card_node *current = deck;
//   struct card_node *prev = NULL;
//   while (current){
//     if (current->face == face && current->suit == suit){
//       if (prev){
//         prev->next = current->next;
//       }
//       else {
//         deck = current->next;
//       }
//       free(current);
//       return deck;
//     }
//     prev = current;
//     current = current->next;
//   }
//   return deck;
// }

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