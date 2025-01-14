.PHONY: compile all clean serve connect run

compile all: client server

client: test_client.o client.o card.o networking.o util.o sigs.o
	@gcc -o client test_client.o client.o card.o networking.o util.o sigs.o
server: server.o card.o deck.o networking.o log.o
	@gcc -o server server.o card.o deck.o networking.o log.o

run:
	@printf "Please run \`make serve\` and \`make connect\`.\n"
connect: client
	@./client
serve: server
	@./server

log.o: log.c log.h
	@gcc -c log.c
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
sigs.o: sigs.c sigs.h
	@gcc -c sigs.c
log.o: log.c log.h
	@gcc -c log.c

clean:
	@rm -rf *.o main client server test_client *.fifo *.out
