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

### 2024-01-03 - Brief description
Expanded description including how much time was spent on task.

## Player 2 -- David Chen

### 2024-01-06 - Beginning layouts
- Copied group Google Doc (for proposals), began laying out main processes. (40m)
- Wrote pseudo-pseudocode outlines for client/server interaction at home. (1h)

### 2024-01-07 - Program Structure
- Merged existing branches so Abigail's `card.h` would be available for use in the client and server. (10m)
- Drew out program structure (subservers forking from main server, like lab15; client as independent program) with Elizabeth (30m)
- Implemented client-side display/input interfaces using `card.h` and new shared `utils.h` function for input. (30m)

### 2024-01-03 - Brief description
Expanded description including how much time was spent on task.

## Abigail Lin

### 2025-01-06 - Created linked list files, added function headers.
Created card.c, card.h, and deck.c. Researched and referenced to past labs to create card.h headers and struct for card_node. Spent the class period.

### 2025-01-06 - Working on implementing functions in card.h.
Implemented createCard, createDeck, printCard and printDeck. Updated card.h to include an array for the suits. Spent around 40 minutes.
