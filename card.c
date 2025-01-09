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
  while (total < 21 && aceCount > 0){
    total += 10;
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
    printf("%s of %s\n",faces[card->face],suits[card->suit]);
    current = current->next;
  }
}

void freeHand(struct card_node *hand){
  struct card_node *current = hand;
  while (current){
    struct card_node *next = current->next;
    free_node(current);
    current = next;
  }
}

// // create a new deck of cards
// void createDeck(struct card_node *deck){
//   struct card_node *current = deck;
//   for (int suit = 0; suit < NUM_SUITS; suit++){
//       for (int face = 0; face < NUM_FACES; face++){
//           struct card_node *newCard = createCard(face, suit, NULL);
//           if (current == NULL){
//               deck = newCard;
//               current = deck;
//           }
//           else {
//               current->next = newCard;
//               current = newCard;
//           }
//       }
//   }
// }

// struct card_node* insert(struct card_node *deck, int face, int suit){
//   struct card_node* newCard = createCard(face, suit, deck);
//   if (newCard == NULL){
//     return deck;
//   }
//   return newCard;
// }

// struct card_node * random_card(struct card_node *card){
//   if (card == NULL) return NULL;
//   int count = 0;
//   struct card_node * temp = card;
//   while (temp != NULL){
//     count++;
//     temp = temp->next;
//   }
//   int end = rand() % count;
//   for (int i = 0; i < end; i++){
//     card = card->next;
//   }
//   return card;
// }

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