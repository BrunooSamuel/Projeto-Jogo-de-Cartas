#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "funcoes.h"
#include "cartas.h"
#include "cartas.c"


int main () {
    carta baralho[56]; //array de todas as cartas, ordenadas por valor
    int linhas; //numero de linhas
    int teste;
    printf("ISTO SÓ SERVE PARA TESTAR SE TEM ALGUMA FALHA\nIndica um numero de uma carta, imprime os 4 naipes dela.\n");
    //scanf("%d", linhas);
    scanf("%d", teste);
    definirCartas(baralho);
    imprimir(teste, baralho);
    return 0;
}