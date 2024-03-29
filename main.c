#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "funcoes.h"
#include "cartas.h"
#include "cartas.c"


int main () {
<<<<<<< Updated upstream
    carta baralho[56]; //array de todas as cartas, ordenadas por valor
    int linhas; //numero de linhas
    int teste;
    printf("ISTO SÓ SERVE PARA TESTAR SE TEM ALGUMA FALHA\nIndica um numero de uma carta, imprime os 4 naipes dela.\n");
    //scanf("%d", linhas);
    scanf("%d", teste);
    definirCartas(baralho);
    imprimir(teste, baralho);
=======
    setlocale(LC_CTYPE, "C.UTF-8");
    //Baralho de cartas, usado malloc para alocar a memória necessária para o baralho
    carta *baralho = malloc(56 * sizeof(carta));

    if (baralho == NULL) {
        printf("Erro ao tentar alocar memória para o baralho.\n");
        return 1;
    }

    // define o baralho
    definirCartas();

    /*
    AQUI FUNCIONA
    wchar_t car;
    wscanf(L"%lc", &car);
    wprintf(L"Simbolo: %lc\n", car);
    wprintf(L"Codigo: %x\n", car);
    MAS DEPOIS NAO FAZ O SCANF
    */ 

    // lê o numero de linhas que recebe
    int linhas=0;
    scanf("%d", &linhas);

    int e=1; // usado no loop embaixo

    while (e<=linhas) 
    {
        lerMao();
        e++;
    }


    free(baralho); // Liberta o espaço na memória alocada para o baralho
>>>>>>> Stashed changes
    return 0;
}