#ifndef LOG_H
#define LOG_H

void create_file(); 
struct player_moves {char name[50]; char card[5]; char move; int winnings;};
void write_file(char * name, char * card, char move, int winnings );
void read_file();

#endif


