CC = gcc
CFLAGS = -Wall -Wextra

all: jogoCartas

jogoCartas: main.o combinacoes.o cartas.o
	$(CC) $(CFLAGS) -o jogoCartas main.o combinacoes.o cartas.o

main.o: main.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c main.c

combinacoes.o: combinacoes.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c combinacoes.c

cartas.o: cartas.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c cartas.c

run: jogoCartas
	./jogoCartas

clean:
	rm -f jogoCartas *.o

debug:
	gdb ./jogoCartas