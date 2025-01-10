#include "card.h"
#include "deck.h"

int main(){
    srand(time(NULL));
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
    struct deck * d = initDeck(1);
    printDeck(d);
    struct card_node * dealtCard = dealRandomCard(d);
    printf("\ndealt card: ");
    printCard(dealtCard);
}
