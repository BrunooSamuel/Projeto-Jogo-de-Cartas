CC = gcc
CFLAGS = -Wall -Wextra

all: jogoCartas

jogoCartas: main.o teste.o
	$(CC) $(CFLAGS) -o jogoCartas main.o teste.o

main.o: main.c funcoes.h
	$(CC) $(CFLAGS) -c main.c

teste.o: teste.c funcoes.h
	$(CC) $(CFLAGS) -c teste.c

run: jogoCartas
	./jogoCartas

clean:
	rm -f jogoCartas *.o