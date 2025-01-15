#ifndef _CLIENT_H
#define _CLIENT_H
void client(int in, int out);

// We use an enum type to define the set of possible actions (to ensure our switch/cases cover all cases)
enum Action {
	NONE,
	PLAY,
	LOGS,
	QUIT
};
#endif
