# Dev Log:

This document must be updated daily by EACH group member.

## Player 1

### 2024-01-06 - Brief description
Expanded description including how much time was spent on task.
Discussed functionalities needed by the server and characteristics of the log .(5 minutes)
Implemented function for creating file and first version of write function (10 minutes)
Decided to use struct data structure, designed struct for game data, rewrote write function and updated header (15 minutes)

Implemented read function with using stat, finished log.c functions (10 minutes)
Researched SIGALRM and sigaction and implemented function to set up signals in sigs.c/h (25 minutes)
Began implementing sighandler for SIGALRM(3 minutes)

### 2024-01-07 - Brief description
Expanded description including how much time was spent on task.
Disccused and implemented sigaction sighandler for SIGINT(5 minutes)
Rediscussed and reorganized server/client structure and pipe structure. (10 minutes)
Started writing custom handshake using prior lab and started forking server (15 minutes)
Wrote outline for play (2 minutes)

Added client handshake and modified to store pid and open a new upstream private pipe(15 minutes)
Started implementing play by adding in card decks and writing and reading player moves, and also implemented game actions for the dealer, player, and processing user input. (35 minutes)
## Player 2 -- David Chen

### 2024-01-06 - Beginning layouts
- Copied group Google Doc (for proposals), began laying out main processes.
- Wrote pseudo-pseudocode outlines for client/server interaction at home.

### 2024-01-03 - Brief description
Expanded description including how much time was spent on task.

## Player 3 -- Abigail Lin

### 2025-01-06 - Created linked list files, added function headers.
Created card.c, card.h, and deck.c. Researched and referenced to past labs to create card.h headers and struct for card_node. Spent the class period.

### 2025-01-06 - Working on implementing functions in card.h.
Implemented createCard, createDeck, printCard and printDeck. Updated card.h to include an array for the suits. Spent around 40 minutes.

### 2025-01-07 - Finishing functions in card, and adding function headers for deck and hand. Starting on the functions.
In class, implmented insert, remove and random for card (class 35~ minutes). At home, finished up remove and free functions for card. Created a new structure hand and deck function headers. (~40 minutes)

### 2025-01-08 - Restructuring card.h
In class, worked on testing/debugging current functions. Redirecting card.h to have more blackjack specific functions. (30 minutes in class)
