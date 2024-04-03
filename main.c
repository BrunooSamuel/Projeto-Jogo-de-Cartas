#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include "funcoes.h"
#include "cartas.h"

int main () {

    //Baralho de cartas, usado malloc para alocar a memória necessária para o baralho
    carta *baralho = malloc(56 * sizeof(carta));

    if (baralho == NULL) {
        printf("Erro ao tentar alocar memória para o baralho.\n");
        return 1;
    }

    // define o baralho
    carta *baralhoDef = definirCartas();

    if (baralhoDef == NULL) {
        printf("Erro ao tentar definir o baralho.\n");
        free(baralho);
        return 1;
    }

    setlocale(LC_CTYPE, "C.UTF-8");
    
    // lê o numero de linhas que recebe
    int linhas;
    wscanf(L"%d", &linhas);

    int e=1; // usado no loop embaixo
    
    limpar();
    while (e<=linhas) 
    {
        //imprimir(1, baralhoDef);
        lerMao(baralhoDef);
        e++;
    }

    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;

}