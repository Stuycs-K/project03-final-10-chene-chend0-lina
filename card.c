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
    printf("%s%s ",faces[current->face],suits[current->suit]);
    current = current->next;
  }
}

void printHandAscii(struct card_node *hand){
  struct card_node *current = hand;
  while (current) { printf("┌───────┐"); current = current->next; }
  printf("\n");

  current = hand;
  while (current) {
    printf("│%-2s     │", faces[current->face]);
    current = current->next;
  }
  printf("\n");

  current = hand;
  while (current) {
    printf("│   %s   │", suits[current->suit]);
    current = current->next;
  }
  printf("\n");

  current = hand;
  while (current) {
    printf("│     %-2s│", faces[current->face]);
    current = current->next;
  }
  printf("\n");

  current = hand;
  while (current) {
    printf("└───────┘");
    current = current->next;
  }
  printf("\n");
}

void printTable(struct card_node *dealer_hand, struct card_node *player_hand, int reveal_dealer) {
  printf("\n=== BLACKJACK ===\n");

  int score = calcHand(dealer_hand);
  if (reveal_dealer == 1){
    printf("\nDealer Score: ???\n");
    printf("┌───────┐ ┌───────┐\n");
    printf("│%-2s     │ │░░░░░░░│\n", faces[dealer_hand->face]);
    printf("│   %s   │ │░░░░░░░│\n", suits[dealer_hand->suit]);
    printf("│     %-2s│ │░░░░░░░│\n", faces[dealer_hand->face]);
    printf("└───────┘ └───────┘\n");
  }
  else {
    printf("\nDealer Score: %d\n", score);
    printHandAscii(dealer_hand);
  }


  printf("\n");

  score = calcHand(player_hand);
	printf("\nPlayer Score: %d\n", score);
	printHandAscii(player_hand);

	printf("\n\n");
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

// moved, makes more sense with card funcs
struct card_node * append_card(struct card_node * original, struct card_node * end) {
	if (!original)
		return end;
	struct card_node *buf = original;
	while (buf->next)
		buf = original->next;
	buf->next = end;
	end->next = NULL;   // redundant but good to be safe
	return original;
}