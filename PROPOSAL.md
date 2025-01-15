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
Server reads a 50-byte string from the user for the user name, then begins the game loop.

Client reads a name from stdin, sends to the server, then begins the game loop.

The game loop begins with the server waiting for the client to send a value of `21` to start the game.

In the game loop, the client reads an int(32) and performs a specific action:
```
  0: no-op
-10: read player card
-11: read dealer card
-12: send move
-13: player wins
-14: player loses
-15: game is a tie
```
For actions -10 & -11, client reads a SINGLE struct card.
For action -12, client sends a move ID.
For actions -15 through -13, client prints out game results, exits.

The server handles validation of game status.

## Processes

Used by the server for per-player subservers.

Dealer (parent) will randomly draw cards, providing setup starting cards for players.

The dealer uses linked lists for shuffling, potentially with multiple decks (dynamically allocated).

Player (child) will have the functions to view game state, send decisions, based on commands from the server.

## Signals

Used for user-invoked exit.

- `SIGINT` to cleanly exit the game, for both client and server.


# Intended pacing:

A timeline with expected completion dates of parts of the project.

1. Design protocol (processes, pipes, commands), blackjack logic (mostly dealer things). Deck shuffling, distributing cards. (1/9)
2. Client and server should be usable for a randomized game. (1/14)
3. Debug, with special attention to signals and semaphores; document functions, test multi-client operation. (1/15)
4. Record first footage for presentation videos. (1/16)
5. Finalize and upload recording, update final README. (1/17)

(1/21) All projects due. Final commits 8am including links to your presentation.
