#ifndef CARD_H
#define CARD_H

#define DECK_SIZE 52
#define NUM_SUITS 4
#define NUM_FACES 13

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// card structure
struct card_node{
    int face;
    int suit;
    struct card_node *next;
};

// faces array
char *faces[] = {"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};

void createDeck(struct card_node *deck);
void printCard(struct card_node *card);
void printDeck(struct card_node *card);
struct card_node* createCard(int face, int suit, struct card_node *next);
struct card_node* insert(int face, int suit, struct card_node * deck);
int compare(struct card_node * a, struct card_node * b);
struct card_node * find_node(struct card_node *card, int face, int suit);
struct card_node * find_face(struct card_node *card, int face);
struct card_node * random_card(struct card_node *card);
struct card_node * remove_card(struct card_node *card, int face, int suit);
void free_node(struct card_node *card);
struct card_node * free_list(struct card_node *card);

#endif