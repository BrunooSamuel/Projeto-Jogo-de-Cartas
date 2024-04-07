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

    // lê o numero de testes
    int numtestes=0;
    if (wscanf(L"%d", &numtestes)==EOF) {
        wprintf(L"O Scan do numero de testes é inválido.\n");
        return 1;
    }

    for (int e1=1; e1<=numtestes; e1++) 
    {   

        int arrayTamanhos[50]={0};
        int arrayCombinacoes[4]={0};

        wprintf(L"Teste %d\n", e1);

        // lê o numero de linhas que recebe de cada teste
        int linhas=0;
        if (wscanf(L"%d", &linhas)==EOF) {
            wprintf(L"O Scan do numero de linhas é inválido.\n");
            return 1;
        }
        int linhasBackup=linhas;
        limpar();

        //array para serem guardados os arrays por ordem que são colocados
        wchar_t todasMaos[linhasBackup][32];
        int posTodasMaos=0;

        for (int e2=1; e2<=linhasBackup ; e2++) 
        {
            //imprimir(6, baralhoDef);
            lerMao(baralhoDef, arrayCombinacoes, arrayTamanhos, &todasMaos[posTodasMaos], posTodasMaos);
            wprintf(L"%d posicao \n", posTodasMaos);
            wprintf(L"%d é o backup \n", linhasBackup);
            posTodasMaos++;
        }
        
        for (int i = 0; i < posTodasMaos; i++)
        {
            wprintf(L"Mao - %ls\n", todasMaos[i]);
        }
        
        bool tamiguais=true;
        CompararTamanhos(arrayTamanhos, &tamiguais);
        bool combiguais=true;
        CompararCombinacao(arrayCombinacoes, linhasBackup, &combiguais);


        compararMaos(baralhoDef, combiguais, tamiguais, *todasMaos, arrayCombinacoes);
    }
    

    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;

}