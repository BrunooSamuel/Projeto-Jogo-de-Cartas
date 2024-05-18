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

    int NumJogAnteriores;
    if (wscanf(L"%d", &NumJogAnteriores)==EOF) {
        return 1;
    }

    limpar();

    processarCodigo(baralhoDef, NumJogAnteriores);
    
    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;
}


void processarCodigo(carta *baralhoDef, int NumJogAnteriores) {

    wchar_t *maoJogador = alocarMao ();
    int tamMaoJogador = lerUmaMao(maoJogador, baralhoDef);
    ordenarMao (baralhoDef, maoJogador, tamMaoJogador);


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

    wchar_t *ultimaJogadaValida = alocarMao ();
    int tamJogadaAnterior=0;
    if (!colocarUltimaJogadaValida(ultimaJogadaValida, jogadasAnteriores, e2-1, arrayTamanhos, &tamJogadaAnterior) || NumJogAnteriores == 0)
    {
        gerarJogadaSemAnterior (baralhoDef,maoJogador, tamMaoJogador);
    } 
    else 
    {
        continuarCodigo(baralhoDef, ultimaJogadaValida, tamJogadaAnterior, maoJogador, tamMaoJogador, numReisAnterior);
    }
}

void gerarJogadaSemAnterior (carta *baralhoDef, wchar_t *maoJogador, int tamMaoJogador) {
    bool jaImprimiu = false;
    int numeroMenor = numeroCarta(baralhoDef, maoJogador[0]);
    int contagem = analisarMao(baralhoDef, maoJogador, numeroMenor, tamMaoJogador);

    //se o numero menor tiver mais que uma carta, gera em primeiro duplas sequências
    if (contagem > 1) {
        int tamanho = 14;
        bool existeDSeq = false;
        while (tamanho >= 6) {
            if (gerarDSeqSemAnterior(baralhoDef, maoJogador, tamanho, tamMaoJogador, &jaImprimiu) == -1) {
            tamanho -= 2;
            } else {
            existeDSeq = true;
            return;
            }
        }

        if (!existeDSeq) 
        {
            if (gerarSequenciaSemAnterior (baralhoDef, maoJogador, tamMaoJogador, 1) == -1){
                ContinuacaoGerarConjunto(baralhoDef, maoJogador, numeroMenor, contagem, tamMaoJogador, 0, &jaImprimiu);
            }
        }

        //se tiver apenas uma carta com o numero menor gera em primeiro sequências
        } else 
        {
            bool existe = false;
            if (gerarSequenciaSemAnterior (baralhoDef, maoJogador, tamMaoJogador, 1) == 0) {
                existe = true;
            }

            if(!existe) {
                ContinuacaoGerarConjunto(baralhoDef, maoJogador, numeroMenor, contagem, tamMaoJogador, 0, &jaImprimiu);
            }
        }
}


void continuarCodigo(carta *baralhoDef, wchar_t *ultimaJogadaValida, int tamJogadaAnterior, wchar_t *maoJogador, int tamMaoJogador, int numReisAnterior) {
    
    ordenarMao (baralhoDef, ultimaJogadaValida, tamJogadaAnterior);

    wchar_t codigoMaisAltaAnterior=ultimaJogadaValida[tamJogadaAnterior-1];
    int valorMaisAltaAnterior=valorDaCartaMaisAlta (baralhoDef, ultimaJogadaValida, tamJogadaAnterior);  

    int combAnterior=devolveCombinacao (ultimaJogadaValida, tamJogadaAnterior, baralhoDef);

    bool jaImprimiu=false;

    int numeroMaisAlta=numeroCarta(baralhoDef, codigoMaisAltaAnterior);


    if (combAnterior==0) 
    {
        if (tamJogadaAnterior==1) cartaIsolada (baralhoDef, maoJogador, valorMaisAltaAnterior, tamMaoJogador, numReisAnterior, &jaImprimiu);
        else gerarConjunto(baralhoDef, maoJogador, valorMaisAltaAnterior, numeroMaisAlta, tamJogadaAnterior, tamMaoJogador, numReisAnterior, &jaImprimiu);
    }
    else if (combAnterior==1) gerarSequencia(baralhoDef, maoJogador, ultimaJogadaValida, valorMaisAltaAnterior, tamJogadaAnterior, tamMaoJogador, numReisAnterior);
    else if (combAnterior==2) gerarDuplaSequencia(baralhoDef, maoJogador, ultimaJogadaValida, valorMaisAltaAnterior, tamJogadaAnterior, tamMaoJogador, numReisAnterior, &jaImprimiu);

    if (numReisAnterior==1) 
    {
        gerarConjunto(baralhoDef, maoJogador, 0, 1, 4, tamMaoJogador, numReisAnterior, &jaImprimiu);
        gerarDuplaSeqEspeciaisReis (baralhoDef, maoJogador, 6, tamMaoJogador, &jaImprimiu);//dupla sequencia tamanho 3
    }
    else if (numReisAnterior==2) gerarDuplaSeqEspeciaisReis (baralhoDef, maoJogador, 8, tamMaoJogador, &jaImprimiu);//dupla sequencia tamanho 4
    else if (numReisAnterior==3) gerarDuplaSeqEspeciaisReis (baralhoDef, maoJogador, 10, tamMaoJogador, &jaImprimiu);//dupla sequencia tamanho 6
}