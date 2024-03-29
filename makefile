CC = gcc
CFLAGS = -Wall -Wextra -g

all: jogoCartas

jogoCartas: main.o combinacoes.o cartas.o testes.o
	$(CC) $(CFLAGS) -o jogoCartas main.o combinacoes.o cartas.o testes.o

main.o: main.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c main.c

combinacoes.o: combinacoes.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c combinacoes.c

cartas.o: cartas.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c cartas.c

testes.o: testes.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c testes.c

run: jogoCartas
	./jogoCartas

clean:
	rm -f jogoCartas *.o

debug:
	gdb ./jogoCartas