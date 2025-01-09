#include "card.h"
#include "deck.h"
#include "card.c"
#include "deck.c"

int main(){
    printf("adding cards to a hand\n");
    struct card_node * hand = NULL;
    addCardToHand(&hand, createCard(10,1,NULL));
    addCardToHand(&hand, createCard(2,2,NULL));
    addCardToHand(&hand, createCard(0,3,NULL));
    addCardToHand(&hand, createCard(0,2,NULL));
    printHand(hand);
    int score = calcHand(hand);
    printf("score: %d\n",score);

    printf("\ndealing cards:\n");
    struct deck * d = createDeck();
    printDeck(d);
    struct card_node * dealtCard = dealCard(d);
    printf("dealt card: ");
    printCard(dealtCard);
    // createDeck(deck);
    // printDeck(deck);

    // for (int face = 0; face < NUM_FACES; face++){
    //     for (int suit = 0; suit < NUM_SUITS; suit++){
    //         deck = insert(deck, face, suit);
    //     }
    // }
    // printf("creating five cards\n");
    // for (int i = 0; i < 5; i++){
    //     insert(deck, 0, 0);
    // }
}
