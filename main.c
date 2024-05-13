#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include "cartas.h"
#include <time.h>
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

    limpar();

    processarCodigo(baralhoDef);
    
    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;
}

void processarCodigo(carta *baralhoDef) {
    
    int NumJogAnteriores=scanInt();
    //wprintf(L"Numero de jogadas anteriores: %d\n", NumJogAnteriores);
        
    wchar_t *maoJogador = alocarMao ();
    int tamMaoJogador = lerUmaMao(maoJogador, baralhoDef);
    ordenarMao (baralhoDef, maoJogador, tamMaoJogador);
    //wprintf(L"Mao Inicial:\n%ls", maoJogador); //teste


    int *arrayTamanhos=alocarArrayInt(NumJogAnteriores);
    int *arrayComb=alocarArrayInt(NumJogAnteriores);
    
    wchar_t *jogadasAnteriores=alocarArrayWchar (arrayTamanhos, arrayComb, NumJogAnteriores);

    int e2=0;
    while (e2<NumJogAnteriores)   
    {
        arrayTamanhos[e2]=lerMao(baralhoDef, arrayComb, jogadasAnteriores, &e2, arrayTamanhos);
    }

    // se e2 for diferente de 0, vai realizar a contadorReis, caso contrario, fica 0
    int numReisAnterior = e2 != 0 ? contadorReis(baralhoDef, jogadasAnteriores, e2 - 1) : 0;

    

    wchar_t codigoMaisAltaAnterior=jogadaAnterior[tamJogadaAnterior-1];
    int valorMaisAltaAnterior=valorDaCartaMaisAlta (baralhoDef, jogadaAnterior, tamJogadaAnterior);
    //wprintf(L"Carta mais alta da jogada anterior : %lc\tO valor dela é %d\nO Numero de reis é %d\n", codigoMaisAltaAnterior,valorMaisAltaAnterior,numReisAnterior);


    int combAnterior=devolveCombinacao (jogadaAnterior, tamJogadaAnterior, baralhoDef);
    //wprintf(L"A jogada anterior era de combinação: %d\n", combAnterior);

    bool jaImprimiu=false;

    int numeroMaisAlta=numeroCarta(baralhoDef, codigoMaisAltaAnterior);


        if (combAnterior==0) 
        {
            if (tamJogadaAnterior==1) cartaIsolada (baralhoDef, maoJogador, valorMaisAltaAnterior, tamMaoJogador, numReisAnterior, &jaImprimiu);
            else gerarConjunto(baralhoDef, maoJogador, valorMaisAltaAnterior, numeroMaisAlta, tamJogadaAnterior, tamMaoJogador, numReisAnterior, &jaImprimiu);
        }
        else if (combAnterior==1) gerarSequencia(baralhoDef, maoJogador, jogadaAnterior, valorMaisAltaAnterior, tamJogadaAnterior, tamMaoJogador, numReisAnterior);
        else if (combAnterior==2) gerarDuplaSequencia(baralhoDef, maoJogador, jogadaAnterior, valorMaisAltaAnterior, tamJogadaAnterior, tamMaoJogador, numReisAnterior, &jaImprimiu);

        //wprintf(L"%d REIS!\n", numReisAnterior);
        if (numReisAnterior==1) 
        {
            gerarConjunto(baralhoDef, maoJogador, 0, 1, 4, tamMaoJogador, numReisAnterior, &jaImprimiu);
            gerarDuplaSeqEspeciaisReis (baralhoDef, maoJogador, 6, tamMaoJogador, &jaImprimiu);//dupla sequencia tamanho 3
        }
        else if (numReisAnterior==2) gerarDuplaSeqEspeciaisReis (baralhoDef, maoJogador, 8, tamMaoJogador, &jaImprimiu);//dupla sequencia tamanho 4
        else if (numReisAnterior==3) gerarDuplaSeqEspeciaisReis (baralhoDef, maoJogador, 10, tamMaoJogador, &jaImprimiu);//dupla sequencia tamanho 6

        free(jogadaAnterior);
        free(maoJogador);
    
}

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // se e2 for diferente de 0, vai realizar a contadorReis, caso contrario, fica 0
        int numReis = e2 != 0 ? contadorReis(baralhoDef, jogadasAnteriores, e2 - 1) : 0;
        // se numReis for maior que 0, vai realizar a verificarJogadaComReis, se não, verificarJogada
        bool valida = numReis > 0 ? verificarJogadacomReis(baralhoDef, jogadaJogador, numReis, tamJogadaJogador) : verificarJogada(baralhoDef, jogadaJogador, jogadasAnteriores, arrayTamanhos, tamJogadaJogador, NumJogAnteriores);
        
        ordenarMao (baralhoDef,maoJogador,tamMaoJogador);
        
        if(valida) verificarCartasMao(maoJogador, jogadaJogador, &tamMaoJogador);
        else tamMaoJogador--; //porque quando nao é alterada, imprime com um \n a mais

        if (tamMaoJogador>=0) imprimirUmaMao (maoJogador);
    
        libertarTodas (arrayTamanhos,arrayComb,jogadasAnteriores,maoJogador,jogadaJogador);