#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include "funcoes.h"
#include "cartas.h"

int main () {
    setlocale(LC_CTYPE, "C.UTF-8");
    //Baralho de cartas, usado malloc para alocar a memória necessária para o baralho
    carta *baralho = malloc(56 * sizeof(carta));

    if (baralho == NULL) {
        printf("Erro ao tentar alocar memória para o baralho.\n");
        return 1;
    }

    // define o baralho
    definirCartas();

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
    return 0;
}