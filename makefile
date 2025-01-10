.PHONY: compile all clean serve connect

compile all: client server

client: test_client.o client.o card.o networking.o util.o
	@gcc -o client test_client.o client.o card.o networking.o util.o
server: server.o card.o deck.o networking.o
	@gcc -o server server.o card.o deck.o networking.o

connect: client
	@./client
serve: server
	@./server

test_client.o: test_client.c client.h card.h
	@gcc -c test_client.c
client.o: client.c client.h card.h util.h
	@gcc -c client.c
server.o: server.c server.h
	@gcc -c server.c
util.o: util.c util.h
	@gcc -c util.c
card.o: card.c card.h
	@gcc -c card.c
deck.o: deck.c deck.h card.h
	@gcc -c deck.c
networking.o: networking.c networking.h
	@gcc -c networking.c

clean:
	@rm -rf *.o main test_client *.fifo
