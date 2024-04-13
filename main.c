#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include "cartas.h"

int main () {

    //Baralho de cartas, usado malloc para alocar a memória necessária para o baralho
    carta *baralho = malloc(56 * sizeof(carta));

    if (baralho == NULL) {
        return 1;
    }

    // define o baralho
    carta *baralhoDef = definirCartas();

    if (baralhoDef == NULL) {
        free(baralho);
        return 1;
    }

    setlocale(LC_CTYPE, "C.UTF-8");

    int numtestes=scanInt(baralho);
    
    for (int e1=1; e1<=numtestes;e1++) 
    {
        wprintf(L"Teste %d\n", e1);

        // lê o numero de linhas que recebe
        int linhas=scanInt(baralho);
        
        limpar();

        int *arrayTamanhos=alocarArrayInt(baralho, linhas);

        int *arrayComb=alocarArrayInt(baralho, linhas);

        wchar_t *todasMaos=alocarArrayWchar (baralho, arrayTamanhos, arrayComb, linhas);

        int tamanho=0;
        for (int e2=0; e2<linhas; e2++)   
        {
            //imprimir(6, baralhoDef);
            tamanho=lerMao(baralhoDef, arrayComb, todasMaos, e2, arrayTamanhos);
            arrayTamanhos[e2]=tamanho;
        }
        
        bool tamIguais= compararTamanhos(arrayTamanhos,linhas);
        bool comIguais= compararCombinacoes(arrayComb);

        if (!tamIguais||!comIguais) wprintf(L"Combinações não iguais!\n");

        else {
            ordenarTudo (baralhoDef, todasMaos, tamanho, linhas);

            maosCrescente (baralhoDef, todasMaos, tamanho, linhas, arrayTamanhos);
        }


        libertarTodas (arrayTamanhos,arrayComb,todasMaos);

    }
    
    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;

}