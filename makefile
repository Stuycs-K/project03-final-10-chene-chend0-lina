.PHONY: run compile all clean test
main: main.o client.o server.o util.o card.o
	@gcc -o main main.o client.o server.o util.o card.o
main.o: main.c
	@gcc -c main.c
test_client.o: test_client.c client.h card.h
	@gcc -c test_client.c
test_client: test_client.o client.o util.o card.o
	@gcc -o test_client test_client.o client.o util.o card.o
test: test_client
	@./test_client
client.o: client.c client.h card.h util.h
	@gcc -c client.c
server.o: server.c server.h
	@gcc -c server.c
util.o: util.c util.h
	@gcc -c util.c
card.o: card.c card.h
	@gcc -c card.c
run all: main
	@./main

clean:
	@rm -rf *.o main test_client
