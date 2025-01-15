#include "card.h"

// takes face, suit, and pointer of the next card
// creates a card
// returns a card_node* to the new card
struct card_node* createCard(int face, int suit, struct card_node *next){
    struct card_node *newCard = (struct card_node*)malloc(sizeof(struct card_node));
    newCard->face = face;
    newCard->suit = suit;
    newCard->next = next;
    return newCard;
}

// takes card_node* of card
// frees card
void freeCard(struct card_node *card){
  if (card){
    free(card);
  }
}

// takes card_node* of start of hand
// calculates hand, including ace if not over 21
// returns hand value
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

// takes a chard_node **hand, and card to add
// adds the new card to the hand
void addCardToHand(struct card_node **hand, struct card_node *card){
  if (!card) return;
  card->next = *hand;
  *hand = card;
}

// takes a card_node *hand
// prints the hand
void printHand(struct card_node *hand){
  struct card_node *current = hand;
  while (current){
    printf("%s%s ",faces[current->face],suits[current->suit]);
    current = current->next;
  }
}

// takes a card_node *hand
// prints the hand with ASCII characters
void printHandAscii(struct card_node *hand){
  struct card_node *current = hand;
  while (current) { printf("┌─────┐"); current = current->next; }
  printf("\n");

  current = hand;
  while (current) {
    printf("│%-2s   │", faces[current->face]);
    current = current->next;
  }
  printf("\n");

  current = hand;
  while (current) {
    printf("│  %s  │", suits[current->suit]);
    current = current->next;
  }
  printf("\n");

  current = hand;
  while (current) {
    printf("│   %-2s│", faces[current->face]);
    current = current->next;
  }
  printf("\n");

  current = hand;
  while (current) {
    printf("└─────┘");
    current = current->next;
  }
  printf("\n");
}

// takes pointer to dealer_hand, player_hand, and if dealer should reveal cards (player stands)
// returns table with ASCII table
void printTable(struct card_node *dealer_hand, struct card_node *player_hand, int reveal_dealer) {
  printf("\n=== BLACKJACK ===\n");

  int score = calcHand(dealer_hand);
  if (reveal_dealer == 1){
    printf("\nDealer Score: ???\n");
    printf("┌─────┐ ┌─────┐\n");
    printf("│%-2s   │ │░░░░░│\n", faces[dealer_hand->face]);
    printf("│  %s  │ │░░░░░│\n", suits[dealer_hand->suit]);
    printf("│   %-2s│ │░░░░░│\n", faces[dealer_hand->face]);
    printf("└─────┘ └─────┘\n");
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

// takes hand pointer
// frees all cards in hand
void freeHand(struct card_node *hand){
  struct card_node *current = hand;
  while (current){
    struct card_node *next = current->next;
    freeCard(current);
    current = next;
  }
}

// takes card_node *card
// prints regular card
void printCard(struct card_node *card){
  if (card){
      printf("%s of %s\n",faces[card->face],suits[card->suit]);
  }
}

// takes hand to check
// returns 1 if blackjack found, 0 if not found
int isBlackjack(struct card_node *hand){
  if (!hand || !hand-> next) return 0;
  struct card_node *first = hand;
  struct card_node *second = hand->next;
  if ( (first->face == 0 && second->face >= 9) || (second->face == 0 && first->face >= 9)){
    return 1;
  }
  return 0;
}

// takes hand to check
// returns 1 if hand is over 21 (bust), 0 if hand is under 21
int isBust(struct card_node *hand){
  int score = calcHand(hand);
  if (score > 21){
    return 1;
  }
  else {
    return 0;
  }
}

// takes pointer to hand, and pointer of end card
// returns pointer to start of hand
struct card_node * append_card(struct card_node * original, struct card_node * end) {
	if (!original)
		return end;
	struct card_node *buf = original;
	while (buf->next)
		buf = buf->next;
	buf->next = end;
	end->next = NULL;   // redundant but good to be safe
	return original;
}
