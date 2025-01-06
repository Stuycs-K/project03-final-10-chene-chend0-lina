.PHONY: run compile all
main: main.o
	@gcc -o main main.o
main.o: main.c
	@gcc -c main.c


run all: main
	@./main
