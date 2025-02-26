.PHONY: compile all clean serve connect run

compile all: client server

# set FLAGS=-g for Valgrind-able builds
client: client.o card.o log.o networking.o util.o
	@gcc $(FLAGS) -o client client.o card.o log.o networking.o util.o
server: server.o card.o deck.o networking.o log.o util.o
	@gcc $(FLAGS) -o server server.o card.o deck.o networking.o log.o util.o

run:
	@printf "Please run \`make serve\` and \`make connect\`.\n"
connect: client
	@./client
serve: server
	@./server

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
log.o: log.c log.h
	@gcc -c log.c

clean:
	@rm -rf *.o main client server test_client *.fifo *.out *.dat
