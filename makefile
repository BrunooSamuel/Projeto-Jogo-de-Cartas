CC = gcc
CFLAGS = -Wall -Wextra -g

all: jogoCartas

jogoCartas: main.o combinacoes.o cartas.o funcoes.o comparacoes.o
	$(CC) $(CFLAGS) -o jogoCartas main.o combinacoes.o cartas.o funcoes.o comparacoes.o

main.o: main.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c main.c

combinacoes.o: combinacoes.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c combinacoes.c

cartas.o: cartas.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c cartas.c

funcoes.o: funcoes.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c funcoes.c

comparacoes.o: comparacoes.c funcoes.h cartas.h
	$(CC) $(CFLAGS) -c comparacoes.c

run: jogoCartas
	./jogoCartas

clean:
	rm -f jogoCartas *.o

debug:
	gdb ./jogoCartas