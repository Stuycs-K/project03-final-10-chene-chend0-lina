#ifndef _UTIL_H
#define _UTIL_H
void fatal(const char *title);
ssize_t safe_getline(char ** lineptr, size_t * n, FILE * stream);
ssize_t safe_read(int fd, void * buf, size_t n);
ssize_t safe_write(int fd, void * buf, size_t n);

enum Move {
	NO_MOVE,
	HIT,
	STAND
};
#endif
