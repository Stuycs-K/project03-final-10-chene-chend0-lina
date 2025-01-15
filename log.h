#ifndef LOG_H
#define LOG_H

void create_file(); 
struct player_moves {char name[50]; char result[10]; int playerscore; int dealerscore; };
void write_file(char * name, char * result, int player_score, int dealer_score);
void read_file();

#endif


