#include "card.h"

// create individual card
struct card_node* createCard(int face, int suit, struct card_node *next){
    struct card_node *newCard = (struct card_node*)malloc(sizeof(struct card_node));
    newCard->face = face;
    newCard->suit = suit;
    newCard->next = next;
    return newCard;
}

void freeCard(struct card_node *card){
  if (card){
    free(card);
  }
}

int calcHand(struct card_node *hand){
  int total = 0;
  int aceCount = 0;
  struct card_node *current = hand;
  while (current){
    // not ace, but keeps track
    if (current->face == 0){
      aceCount++;
    }
    else {
      if (current->face > 9){
        total += 10;
      }
      else {
        total += current->face + 1;
      }
    }
    current = current->next;
  }
  while (total+11 <= 21 && aceCount > 0){
    total += 11;
    aceCount--;
  }
  while (aceCount > 0){
    total++;
    aceCount--;
  }
  return total;
}

void addCardToHand(struct card_node **hand, struct card_node *card){
  if (!card) return;
  card->next = *hand;
  *hand = card;
}

void printHand(struct card_node *hand){
  struct card_node *current = hand;
  while (current){
    printf("%s of %s\n",faces[current->face],suits[current->suit]);
    current = current->next;
  }
}

void freeHand(struct card_node *hand){
  struct card_node *current = hand;
  while (current){
    struct card_node *next = current->next;
    freeCard(current);
    current = next;
  }
}

// utility functions
void printCard(struct card_node *card){
  if (card){
      printf("%s of %s\n",faces[card->face],suits[card->suit]);
  }
}

int isBlackjack(struct card_node *hand){
  if (!hand || !hand-> next) return 0;
  struct card_node *first = hand;
  struct card_node *second = hand->next;
  if ( (first->face == 0 && second->face >= 9) || (second->face == 0 && first->face >= 9)){
    return 1;
  }
  return 0;
}

int isBust(struct card_node *hand){
  int score = calcHand(hand);
  if (score > 21){
    return 1;
  }
  else {
    return 0;
  }
}

// struct card_node* insert(struct card_node *deck, int face, int suit){
//   struct card_node* newCard = createCard(face, suit, deck);
//   if (newCard == NULL){
//     return deck;
//   }
//   return newCard;
// }
