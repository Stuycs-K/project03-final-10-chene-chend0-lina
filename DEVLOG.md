# Dev Log:

This document must be updated daily by EACH group member.

## Player 1 -- Elizabeth Chen

### 2024-01-06 - Implemented file log writing and sighandler for sigalrm
Expanded description including how much time was spent on task.
Discussed functionalities needed by the server and characteristics of the log .(5 minutes)
Implemented function for creating file and first version of write function (10 minutes)
Decided to use struct data structure, designed struct for game data, rewrote write function and updated header (15 minutes)

Implemented read function with using stat, finished log.c functions (10 minutes)
Researched SIGALRM and sigaction and implemented function to set up signals in sigs.c/h (25 minutes)
Began implementing sighandler for SIGALRM(3 minutes)

### 2024-01-07 - Implemented sighandler for sigint and wrote handshake
Expanded description including how much time was spent on task.
Disccused and implemented sigaction sighandler for SIGINT(5 minutes)
Rediscussed and reorganized server/client structure and pipe structure. (10 minutes)
Started writing custom handshake using prior lab and started forking server (15 minutes)
Wrote outline for play (2 minutes)

Added client handshake and modified to store pid and open a new upstream private pipe(15 minutes)
Started implementing play by adding in card decks and writing and reading player moves, and also implemented game actions for the dealer, player, and processing user input. (35 minutes)

### 2024-01-08 - Implemented headers/flags in downstream private pipe and fixed game logic
Fixed messages on server end. (2 minutes). In class, discussed how client knows what to read and do from server, implemented pipe headers for client, and fixed logic of checking total value of player's cards. (30 minutes).

At home, changed flags, client reads int instead. Updated play() to send flags when before sending cards and changed order of assigning values to be able to send card_node to client. Also fixed wrong sizeof() when card_nodes to client. Also implemented dealer hitting cards until total value reaches 17 and begain implementing results and blackjack status. (1 hour)

### 2024-01-9 - Implemnted result logic
Accounted for all of the different possible outcomes and implemented them (20 minutes). Also began writing more error messages. (5 minutes)
At home, set up and implemented semaphores for write, fixed sigint_handler to remove semaphores (30 minutes) Also changed sigalrm_handler and set up timer in play. (15 minutes).

### 2024-01-10 - Persistent Server and forgot own code???
In class, made the server into a persistent server by setting up new header and also checked networking.c code for write to_client (15 minutes). Changed all return values for exit values and added error messages through out the code (10 minutes). A

### 2024-01-12 -- At home for 1/10
Added calcCard to calculate the specific value of card with aces (1 or 11). Fixed server to use calcCard to add card value. Debugged syntax errors and moved sigalrm_handler to server because of extern issue. At hom, server also now removes semaphore if cannot get semaphore due to sigint on server(will probably need to do sigint handler) (1 hour)

### 2024-01-13
In class, rewrote server using methods from card.c and deck.c. (Class period) At home, fixed logic for calcCard, updated user interface with results, and modified data struct for log. (30 minutes)

### 2024-01-14
In class, fixing branch (15 min). Testing blackjack simulation (5 min). Discussed data structures for log and result and decided to store name (5 min). Updated methods in server to reflect changes in log and result (10 min). At home, tried to get sigalrm working, failed. Fixed removing wkp and semaphore in sigalrm_handler. Also updated documentation to clarify methods. (30 minutes)

## Player 2 -- David Chen

### 2024-01-06 - Beginning layouts
- Copied group Google Doc (for proposals), began laying out main processes. (40m)
- Wrote pseudo-pseudocode outlines for client/server interaction at home. (1h)

### 2024-01-07 - Program Structure
- Merged existing branches so Abigail's `card.h` would be available for use in the client and server. (10m)
- Drew out program structure (subservers forking from main server, like lab15; client as independent program) with Elizabeth (30m)
- Implemented client-side display/input interfaces using `card.h` and new shared `utils.h` function for input. (30m)

### 2024-01-08 - Client/Server Protocols
- Discussed and designed a command-based communication protocol for allowing the server to manipulate client state and activity with Elizabeth (40m)
- Implemented client functionality according to said specification, tested with mocked server input. (40m)

### 2024-01-09 - We Don't Know How To Play Blackjack
- Reviewed necessary deck access features (drawing random card) with Abigail (5m)
- Drew out possible cases for a game's outcome (e.g. hitting a 21 "blackjack" on the first round [can win, lose, tie], possibilities for player that hits/draws/busts, possibilities for dealer drawing) with Elizabeth (20m)
- Merged all three branches with an eye towards allowing the client and server could make full use of Abigail's implemented card handling features (calculation of hand values, randomized draws, etc.), and conference on the handshake protocols. (1h 15m)
  - Built binaries are still in an unstable state, note that the client still uses a mocked file for testing at this time.
  - Fixed a few notable bugs (that prevented successful builds, or on first inspection might have been implemented incorrectly).

### 2025-01-10 - Post-Merge Stress
- Reviewed the use of pipes in the server (5m).
- Discussed next steps and extensions (5m).
- Actually read some of the merged code, edited for SIGINT handling (25m).

### 2025-01-13
- Oops 2AM me didn't push after resolving various merge/build conflicts (edit: merged stuff!)
  - Did another merge, read through everyone's code to get a sense for how things go together, began hooking things up (30m, it was after midnight so sure close enough).
- Outlined video format (10m)
  - (1) Standard playthrough of a single game
     - Discuss underlying card data structure and randomization procedure
     - Discuss the command-based communications protocol
       - Discuss the handshaking mechanisms
       - Discuss the command code structure
  - (2) Simultaneous playthrough of multiple games
     - Discuss forking of processes
  - (3) Display of logs
     - Discuss datastructure of logged events
- Connected client to non-mocked server with actual random cards/outcomes, diagnosed and fixed misimplementations that impeded gameplay. (1 hr)

### 2025-01-14
- Oopsies someone committed to main and broke builds... cherry-picking the good commits to excise the bad one, then having everyone recreate/update their branches as needed. (15m)
- Discussed the scope and design of the log file, modified protocol to support user name entry from the client (for use in the logs). (25m)
- Merged group's work on the log file into one build, fixed implementation bugs (stripping newlines, updated function calls to fit latest prototypes) (20m).
- Tested gameplay, fixed bug with premature blackjacks being visible through the log (added feature for server to block until the client called for a game) (5m).
- Updated the makefile to support the addition of `-g` for debug builds, used Valgrind to hunt down memory leaks and fix them (45m).

### 2025-01-15
- Merged overnight changes (1m)
- Read through server and client code for vestigial code, annotated client with expository comments (35m)
- Tested changes, fixed mostly harmless dealer bug (5m)
- Read through remaining code files, removed more unused code and sprinkled light comments (15m)
- Added remove() call to client SIGINT, add flavor text (30m).

## Player 3 -- Abigail Lin

### 2025-01-06 - Created linked list files, added function headers.
Created card.c, card.h, and deck.c. Researched and referenced to past labs to create card.h headers and struct for card_node. Spent the class period.

### 2025-01-06 - Working on implementing functions in card.h.
Implemented createCard, createDeck, printCard and printDeck. Updated card.h to include an array for the suits. Spent around 40 minutes.

### 2025-01-07 - Finishing functions in card, and adding function headers for deck and hand. Starting on the functions.
In class, implmented insert, remove and random for card (class 35~ minutes). At home, finished up remove and free functions for card. Created a new structure hand and deck function headers. (~40 minutes)

### 2025-01-08 - Restructuring card.h and deck.h
In class, worked on testing/debugging current functions. Redirecting card.h to have more blackjack specific functions. (30 minutes in class)

At home, continued to clean up card.h and deck.h's functions. Finished renaming the old ones in card.c. Started working on deck.c's functions, need to figure bug with dealt cards + find out how to shuffle, esp with multiple decks. (1.5 hr)

### 2025-01-09 - Finish card and deck structures + functions
In class, worked on dealing a random card, fixing bug with printCard double printing. Looking to more funcs to benefit server (30 min)

At home, added isBlackjack and isBust to card.h. Adjusted initdeck in deck.h to take number of decks, cleaned up dealRandomCard. Thinking about adding shufledeck. (30 min)

### 2025-01-10 - Work on replacing client functions + user interface
In class, worked on replacing functions in client.c with functions I already made in card/deck. Working on print functions, might make a new one, to print out card versions + allow client to easily understand the game. (30 min)

### 2025-01-12 - ASCII Cards, End Game Status
Worked on the printing functions, including printing the hands for the cards. If too much, can be switched out. Also, printed out game status at the end. Starting on betting (maybe). (1 hour)

### 2025-01-13 - Update README + logs
In class, computer almost died, so will update card.h at home. Updated README with instructions on current code, need to update current WIP. (30 minutes)

At home, reviewed David's updated code, and worked on implementing the log for player. Fixed minor bugs in log.c, and worked on creating a reset log function. (30 minutes)

### 2025-01-14 - Reworking Logs
In class, worked on re-adding yesterday's log code after the revert to previous commit. Decided to change log to represent game wins only, not cards. Updated writefile and other log functions to match new function. (40 minutes)

At home, finished log code (waiting on David's player username input + Elizabeth's server). Updated log to include both player and dealer score. Moved stuff around while debugging. (30 minutes)

### 2025-01-14 - Debugging, adding blackjack check, function headers
In class, added blackjack check in end result. Started working on function headers, finished card.c, going to work on deck.c (30 minutes)
