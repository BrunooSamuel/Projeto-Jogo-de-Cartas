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
        wprintf(L"Erro ao tentar alocar memória para o baralho.\n");
        return 1;
    }

    // define o baralho
    carta *baralhoDef = definirCartas();

    if (baralhoDef == NULL) {
        wprintf(L"Erro ao tentar definir o baralho.\n");
        free(baralho);
        return 1;
    }

    setlocale(LC_CTYPE, "C.UTF-8");

    int numtestes=0;
    if (wscanf(L"%d", &numtestes)==EOF) {
        wprintf(L"O Scan do numero de testes é inválido.\n");
        free(baralho);
        return 1;
    }
    
    for (int e1=1; e1<=numtestes;e1++) 
    {
        wprintf(L"Teste %d\n", e1);

        // lê o numero de linhas que recebe
        int linhas=0;
        if (wscanf(L"%d", &linhas)==EOF) {
            wprintf(L"O Scan do numero de linhas é inválido.\n");
            free(baralho);
            return 1;
        }
        
        limpar();

        int *arrayTamanhos=malloc((linhas-1)*sizeof(int)); //aloca memoria para o array que vai guardar os tamanhos das linhas
        memset(arrayTamanhos, 0, sizeof(arrayTamanhos[0])*linhas); //coloca tudo a 0 no array
        if (arrayTamanhos == NULL) {
            printf("Erro ao alocar memória para arrayTamanhos.\n");
            free(baralho);
            return 1;
        }

        int *arrayComb=malloc(4*sizeof(int)); //aloca memoria para o array que vai guardar as combinacoes para depois serem comparadas
        memset(arrayComb, 0, sizeof(arrayComb[0])*4); //coloca tudo a 0 no array
        //pos 0 é relativa a conjuntos, pos 1 a sequencias, pos 2 a dupla sequencias e pos 3 a nada
        if (arrayComb == NULL) {
            printf("Erro ao alocar memória para arrayComb.\n");
            free(arrayTamanhos);
            free(baralho);
            return 1;
        }

        wchar_t *todasMaos=malloc(sizeof(wchar_t)*14*linhas); //array para colocar todas as maos
        if (todasMaos == NULL) {
            printf("Erro ao alocar memória para todasMaos.\n");
            free(arrayTamanhos);
            free(arrayComb);
            free(baralho);
            return 1;
        }
        int tamanho;
        for (int e2=1; e2<=linhas; e2++)   
        {
            //imprimir(6, baralhoDef);
            tamanho=lerMao(baralhoDef, arrayComb, todasMaos, (e2-1), arrayTamanhos);
            arrayTamanhos[e2-1]=tamanho;
        }
        

        // teste que imprime para verificar se o todasMaos está correto
        /*
        for (int i = 0; i < linhas; i++) 
        {
            // *indica que a largura é fornececida pelo argumento arrayTamanhos[i]
            wprintf(L"%.*ls\n", arrayTamanhos[i], &todasMaos[i * 14]);
        }
        */
        

        bool tamIguais= compararTamanhos(arrayTamanhos,linhas);
        bool comIguais= compararCombinacoes(arrayComb);

        if (!tamIguais||!comIguais) wprintf(L"Combinações não iguais!\n");

        else {
            ordenarTudo (baralhoDef, todasMaos, tamanho, linhas);

            maosCrescente (baralhoDef, todasMaos, tamanho, linhas);

            // IMPRIME AS MAOS ORDENADAS
            for (int i = 0; i < linhas; i++) 
            {
                // *indica que a largura é fornececida pelo argumento arrayTamanhos[i]
                wprintf(L"%.*ls\n", arrayTamanhos[i], &todasMaos[i * 14]);
            }
        }

        free(arrayTamanhos);
        free(arrayComb);
        free(todasMaos);

    }
    

    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;

}