// Garante que, se o arquivo já foi incluído em algum lugar anteriormente, ele não será incluído novamente
#ifndef CARTAS_H
#define CARTAS_H
#include <wchar.h>

// Estrutura de uma Carta

typedef struct carta {
    wchar_t codigo; //codigo da carta
    int naipe; //naipe da carta (Espadas-1 Copas-2 Ouros-3 Paus-4)
    int numero; //numero da carta (J-11 C-12 Q-13 K-14)
} carta; // Define um tipo de dado com o nome carta


/*
Ordem das Cartas Explicado:

A ordem ascendente dos valores é: A 2 3 4 5 6 7 8 9 10 J C Q K
A ordem dos naipes é: ♠ ♥ ♦ ♣ (Espadas -> Copas -> Ouros -> Paus)

*/

// função que define todas as cartas
void definirCartas(carta baralho[]);

// Esta linha fecha a diretiva #ifndef
#endif