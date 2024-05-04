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
    limpar();
    for (int e1=1; e1<=numtestes;e1++) 
    {
        processarCodigo(e1, baralhoDef);
    }
    
    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;
}

void processarCodigo(int esteTeste, carta *baralhoDef) {

    wprintf(L"Teste %d\n", esteTeste);
    
        wchar_t *jogadaAnterior = alocarMao ();
        int tamJogadaAnterior = lerUmaMao(jogadaAnterior, baralhoDef);
        //wprintf(L"Jogada Anterior: %ls", jogadaAnterior);

        ordenarMao (baralhoDef, jogadaAnterior, tamJogadaAnterior);
        wchar_t codigoMaisAltaAnterior=jogadaAnterior[tamJogadaAnterior-1];
        int valorMaisAltaAnterior=valorDaCartaMaisAlta (baralhoDef, jogadaAnterior, tamJogadaAnterior);
        int numReisAnterior=contadorAuxiliar (baralhoDef, jogadaAnterior);
        //wprintf(L"Carta mais alta da jogada anterior : %lc\tO valor dela é %d\nO Numero de reis é %d\n", codigoMaisAltaAnterior,valorMaisAltaAnterior,numReisAnterior);


        int combAnterior=devolveCombinacao (jogadaAnterior, tamJogadaAnterior, baralhoDef);
        //wprintf(L"A jogada anterior era de combinação: %d\n", combAnterior);

        wchar_t *maoJogador = alocarMao ();
        int tamMaoJogador = lerUmaMao(maoJogador, baralhoDef);
        ordenarMao (baralhoDef, maoJogador, tamMaoJogador);

        //wprintf(L"Mao Inicial: %ls\n", maoJogador);
        bool jaImprimiu=false;
        int numeroMaisAlta=numeroCarta(baralhoDef, codigoMaisAltaAnterior);
        if (combAnterior==0) 
        {
            if (tamJogadaAnterior==1) cartaIsolada (baralhoDef, maoJogador, valorMaisAltaAnterior, tamMaoJogador, numReisAnterior, &jaImprimiu);
            else gerarConjunto(baralhoDef, maoJogador, valorMaisAltaAnterior, numeroMaisAlta, tamJogadaAnterior, tamMaoJogador, numReisAnterior, &jaImprimiu);
        }
        else if (combAnterior==1) gerarSequencia(baralhoDef, maoJogador, jogadaAnterior, valorMaisAltaAnterior, tamJogadaAnterior, tamMaoJogador);
        //else if (combAnterior==2) gerarDuplaSequencia(baralhoDef, maoJogador, valorMaisAltaAnterior, codigoMaisAltaAnterior, tamJogadaAnterior, tamMaoJogador);

        if (numReisAnterior>0) 
        {
            //wprintf(L"%d REIS!\n", numReisAnterior);
            if (numReisAnterior==1) 
            {
                //vem com 0 reis para poder escrever passo se necessário
                gerarConjunto(baralhoDef, maoJogador, 0, 1, 4, tamMaoJogador, 0, &jaImprimiu);
                //dupla sequencia tamanho 3
            }
            else if (numReisAnterior==2) {}//dupla sequencia tamanho 4
            else if (numReisAnterior==3) {}//dupla sequencia tamanho 6
            
        }

        free(jogadaAnterior);
        free(maoJogador);
}
