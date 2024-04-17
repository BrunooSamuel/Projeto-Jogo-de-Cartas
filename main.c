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

    int numtestes=scanInt();
    
    for (int e1=1; e1<=numtestes;e1++) 
    {
        wprintf(L"Teste %d\n", e1);

        // lê o numero de jogadas anteriores que recebe
        int NumJogAnteriores=scanInt();
        
        limpar();

<<<<<<< Updated upstream
        //int *arrayTamanhos=alocarArrayInt(linhas);

        //int *arrayComb=alocarArrayInt(linhas);

        // wchar_t *todasMaos=alocarArrayWchar (arrayTamanhos, arrayComb, linhas);
        
        wchar_t *mao=alocarMao();
        lerMao(mao);

        int e2=linhas;
        while (e2>0)   
        {
            //vem uma mao nova para ser usada
            wchar_t *jogada=alocarMao();


            lerMao(jogada);
            e2--;

            //limpa a mao para dps receber a nova
            free(jogada);
        }
        wchar_t *jogada=alocarMao();
        //recebe a jogada do jogador   
        lerMao(jogada);
        wprintf(L"Mao - %ls", mao);
        wprintf(L"Jogada - %ls\n", jogada);
        //bool tamIguais= compararTamanhos(arrayTamanhos,linhas);
        //bool comIguais= compararCombinacoes(arrayComb);

        //if (!tamIguais||!comIguais) wprintf(L"Combinações não iguais!\n");

        
        //ordenarTudo (baralhoDef, todasMaos, arrayTamanhos[e2-1], linhas);
        //maosCrescente (baralhoDef, todasMaos, arrayTamanhos[e2-1], linhas, arrayTamanhos);
        
=======
        int *arrayTamanhos=alocarArrayInt(NumJogAnteriores);

        int *arrayComb=alocarArrayInt(NumJogAnteriores);
    
        wchar_t *jogadasAnteriores=alocarArrayWchar (arrayTamanhos, arrayComb, NumJogAnteriores);
        
        wchar_t *maoJogador = alocarMao (arrayTamanhos,arrayComb, jogadasAnteriores);
        int tamMaoJogador = lerUmaMao(maoJogador, baralhoDef, arrayComb, jogadasAnteriores, arrayTamanhos);

        int e2=0;
        while (e2<NumJogAnteriores)   
        {
            arrayTamanhos[e2]=lerMao(baralhoDef, arrayComb, jogadasAnteriores, e2, arrayTamanhos);
            e2++;
        }
        wchar_t *jogadaJogador = alocarMao (arrayTamanhos,arrayComb, jogadasAnteriores);
        int tamJogadaJogador = lerUmaMao(jogadaJogador, baralhoDef, arrayComb, jogadasAnteriores, arrayTamanhos);

        //bool tamIguais= compararTamanhos(arrayTamanhos,linhas);
        //bool comIguais= compararCombinacoes(arrayComb);

        // if (!tamIguais||!comIguais) wprintf(L"Combinações não iguais!\n");

        for (int i=0; jogadasAnteriores[i]!='\0'; i++) {
            wprintf(L"%ls", jogadasAnteriores[i]);
            wprintf(L"\n");
        }
>>>>>>> Stashed changes

        // else {
            // ordenarTudo (baralhoDef, jogadasAnteriores, arrayTamanhos[e2-1], linhas);
            // maosCrescente (baralhoDef, jogadasAnteriores, arrayTamanhos[e2-1], linhas, arrayTamanhos);
            ordenarMao (baralhoDef,maoJogador,tamMaoJogador);
        

<<<<<<< Updated upstream
        //libertarTodas (arrayTamanhos,arrayComb,todasMaos);
        free(mao);
=======
>>>>>>> Stashed changes

        libertarTodas (arrayTamanhos,arrayComb,jogadasAnteriores);
        free(jogadaJogador);
        free(maoJogador);
    }
    
    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;
}