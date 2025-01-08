# Final Project Proposal -- Blackjack

**Team**:  2Chenz & Lin-dacris 
## Group Members:

Elizabeth Chen, David Chen (0), Abigail Lin
       
# Intentions:

We want to create singleplayer Blackjack (with an option for cooperative
multiplayer later), which will simulate a game between a dealer and player
(other players may queue to join afterwards using a semaphore-based system).
    
# Intended usage:

Our UI will have an introduction screen with rules and controls that the player
needs to follow. During the game, the player will be able to see the visible
card in the dealer’s hand, and their own. They will be prompted to hit/stand
with a text prompt. The screen will constantly refresh to count down their time.
Screen will refresh upon the player's choice to hit/stand. At the end of the
game, show a win/loss screen with the results of both dealer and player’s hands.
Outside of a round of blackjack, a player client may read the public log of game
moves/results.

  
# Technical Details:

A description of your technical design. This should include:
   
How you will be using the topics covered in class in the project.
     
How you are breaking down the project and who is responsible for which parts.
  
What data structures you will be using and how.
     
What algorithms and /or data structures you will be using, and how.

## Files
Used for a public log of player actions and game results. The central server
process writes to the log, and all clients can read from it.

The log file is protected by a semaphore to prevent simultaneous writes.

### Semaphores

Used to protect the log file and to manage queueing for a game.

## Pipes

Used to communicate between the dealer and player, which are respectively parent
and child processes.
- The dealer sends the game state to the player. (Example: The value of the
  dealer's face-up card).
- Player tells the dealer their choice to either hit or stand through another pipe.

### Protocol
Client reads an int(32) and performs a specific action:
```
-10: read player card
-11: read dealer card
-12: send move
-13: player wins
-14: player loses
```
For actions -10 & -11, client reads a SINGLE struct card.
For action -12, client sends a move ID.
For actions -13 & -14, client prints out game results, exits.

## Processes

Used to differentiate between dealer and player.

Dealer (parent) will have the functions to shuffle the deck, setup starting cards for players.

The dealer uses linked lists for shuffling, potentially with multiple decks (dynamically allocated).

Player (child) will have the functions to view game state, send decisions.

## Signals

Used for user timeouts and exits.

- `SIGINT` to save game state, and allow for another player to enter the game
- `SIGALRM` for a time limit on players, to which they will be warned before being kicked from the game.


# Intended pacing:

A timeline with expected completion dates of parts of the project.

1. Finish simple blackjack, mostly dealer things. Deck shuffling, distributing cards. (1/9)
2. Finish forking and processes and pipes (1/14)
3. Finish semaphores (1/14)
4. Finish signals (1/15)
5. Single-player is done (logs, pipes, signals)
6. Extend to multiple client programs (1/17)
7. Finish recording presentation, finalize README (1/20)

(1/21) All projects due. Final commits 8am including links to your presentation.
