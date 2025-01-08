#ifndef _UTIL_H
#define _UTIL_H
void fatal(const char *title);
ssize_t safe_getline(char ** lineptr, size_t * n, FILE * stream);

enum Move {
	NO_MOVE,
	HIT,
	STAND
};
#endif
