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

void printDeck(struct card_node *deck){
    struct card_node *current = deck;
    while (current){
        printCard(current);
        current = current->next;
    }
}

struct card_node* insert(struct card_node *deck, int face, int suit){
  struct card_node* newCard = createCard(face, suit, deck);
  if (newCard == NULL){
    return deck;
  }
  return newCard;
}

struct card_node * find_node(struct card_node *card, int face, int suit){
  while (card != NULL){
    if (card->face == face && card->suit == suit){
      return card;
    }
    card = card->next;
  }
  return NULL;
}

struct card_node * random_card(struct card_node *card){
  if (card == NULL) return NULL;
  int count = 0;
  struct card_node * temp = card;
  while (temp != NULL){
    count++;
    temp = temp->next;
  }
  int end = rand() % count;
  for (int i = 0; i < end; i++){
    card=  card->next;
  }
  return card;
}
