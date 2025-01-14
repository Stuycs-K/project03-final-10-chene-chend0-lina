#ifndef LOG_H
#define LOG_H

void create_file(); 
// struct player_moves {char name[50]; char card[5]; char move; int winnings;};
struct player_moves {char name[50]; char result[5]; };
void write_file(char * name, char * result);
void read_file();

#endif


