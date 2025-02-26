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
with a text prompt. Screen will refresh upon the player's choice to hit/stand. At the end of the
game, show a win/loss screen with the results of both dealer and player’s hands.
Outside of a round of blackjack, a player client may read the public log of game
moves/results.

  
# Technical Details:

A description of your technical design. This should include:

How you will be using the topics covered in class in the project.

How you are breaking down the project and who is responsible for which parts.

What data structures you will be using and how.

What algorithms and /or data structures you will be using, and how.

## Processes

Used by the server for per-player subservers.

Dealer (parent) will randomly draw cards, providing setup starting cards for players.

The dealer uses linked lists for shuffling, potentially with multiple decks (dynamically allocated).

Player (child) will have the functions to view game state, send decisions, based on commands from the server.

## Signals

Used for user-invoked exit.

- `SIGINT` to cleanly exit the game, for both client and server.
  
## Files
Used for a public log of player actions and game results. The central server
process writes to the log, and all clients can read from it.

The log file is protected by a semaphore to prevent simultaneous writes.

## Semaphores

Used to protect the log file and to manage queueing for a game.

## Pipes
Used to communicate between the dealer and player, which are respectively parent
and child processes.
- The dealer sends the game state to the player. (Example: The value of the
  dealer's face-up card).
- Player tells the dealer their choice to either hit or stand through another pipe.

# Breaking It Down
We are breaking it down into three main parts: the server, client, and card/deck functionalities. Elizabeth is responsible for the server, which includes setting up handshakes/pipes and the game proccess. David is responsible for the client, which includes reading game data from the server and the UI. Abigail is responsible for the card functionalities (random cards, printing cards, etc) and the result log.
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




# Intended pacing:

A timeline with expected completion dates of parts of the project.

1. Design protocol (processes, pipes, commands), blackjack logic (mostly dealer things). Deck shuffling, distributing cards. (1/9)
2. Client and server should be usable for a randomized game. (1/14)
3. Debug, with special attention to signals and semaphores; document functions, test multi-client operation. (1/15)
4. Record first footage for presentation videos. (1/16)
5. Finalize and upload recording, update final README. (1/17)

(1/21) All projects due. Final commits 8am including links to your presentation.

# Data Structures
We will be using structs to store and manage game states.

`struct card_node`
- Contains card information
  - Face (0-12): Ace, 2..10, Jack, Queen, King
  - Suit (0-3): Hearts, Diamonds, Clubs, Spades
- Singly-linked list node via the `next` pointer
- A NULL-terminated linked list of `card_node`s represents a hand of cards, and we can calculate the cards' total value (which must be dynamic, as Aces can be worth 1 or 11 based on which benefits the player most).


`struct deck`
- Wrapper to a linked list of `card_node`, which has an `int size` carrying the length.
- `dealRandomCard(struct deck *)` depends on the `size` to efficiently draw a random card.
  - We generate a random index from 0 to the `size` of the linked list.
  - We access and remove that element from the linked list, and decrement `size`.
    - By using a linked list, we avoid the need to resize/shift the array when excising a drawn card.

`struct player_moves`
- Encodes the results of a game, including
  - User name (50-char string)
  - Win/Loss/Tie (10-char string)
  - Card value of the player's hand
  - Card value of the dealer's hand
