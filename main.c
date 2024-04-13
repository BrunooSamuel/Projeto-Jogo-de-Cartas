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
    carta *baralho = alocarArrayCartas();

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
        
        int e2=0;
        while (e2<linhas)   
        {
            //imprimir(6, baralhoDef);
            arrayTamanhos[e2]=lerMao(baralhoDef, arrayComb, todasMaos, e2, arrayTamanhos);
            e2++;
        }
        
        bool tamIguais= compararTamanhos(arrayTamanhos,linhas);
        bool comIguais= compararCombinacoes(arrayComb);

        if (!tamIguais||!comIguais) wprintf(L"Combinações não iguais!\n");

        else {
            ordenarTudo (baralhoDef, todasMaos, arrayTamanhos[e2-1], linhas);
            maosCrescente (baralhoDef, todasMaos, arrayTamanhos[e2-1], linhas, arrayTamanhos);
        }


        libertarTodas (arrayTamanhos,arrayComb,todasMaos);

    }
    
    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;

}