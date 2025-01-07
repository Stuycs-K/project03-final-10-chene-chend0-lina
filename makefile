.PHONY: run compile all clean
main: main.o client.o server.o util.o
	@gcc -o main main.o client.o server.o util.o
main.o: main.c
	@gcc -c main.c
client.o: client.c client.h
	@gcc -c client.c
server.o: server.c server.h
	@gcc -c server.c
util.o: util.c util.h
	@gcc -c util.c
run all: main
	@./main

clean:
	@rm -rf *.o main
