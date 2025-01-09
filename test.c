#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "card.c" // look into that one

int main(){
    printf("creating a deck (1 for now)\n");
    struct card_node* deck = NULL;
    // for (int face = 0; face < NUM_FACES; face++){
    //     for (int suit = 0; suit < NUM_SUITS; suit++){
    //         deck = insert(deck, face, suit);
    //     }
    // }
    createDeck(deck);
    printDeck(deck);
    // printf("creating five cards\n");
    // for (int i = 0; i < 5; i++){
    //     insert(deck, 0, 0);
    // }
}
