CC = gcc
CFLAGS = -Wall -Wextra -g
SRCS = main.c combinacoes.c cartas.c funcoes.c comparacoes.c pares.c
HDRS = funcoes.h cartas.h
ZIP_DIR = ./

all: jogoCartas

jogoCartas: $(SRCS:.c=.o)
	$(CC) $(CFLAGS) -o jogoCartas $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $<

run: jogoCartas
	./jogoCartas

clean:
	rm -f jogoCartas *.o
	rm -f $(ZIP_DIR)CC207_GUIAO3.zip
	@echo "🧹 Limpeza concluída 🧹"

debug:
	gdb ./jogoCartas

zip:
	zip $(ZIP_DIR)CC207_GUIAO3.zip $(SRCS) $(HDRS) makefile
	@echo "📦 ZIP criado com sucesso 📦"