#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"


void gerarConjunto (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamanho) {
    wprintf(L"Veio para gerar Conjunto\n");


}

void gerarSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamanho) {
    wprintf(L"Veio para gerar Sequencia\n");


}

void gerarDuplaSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Dupla Sequencia\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta); 

    //encontrar a carta maior que a carta mais alta da jogada anterior
    for (int i = 0; i < tamMao; i++){ 

        int numeroMaior = numeroCarta (baralho, mao[i]);

        //verificar se tem dupla
        if(numeroMaior > numeroMaisAlta) {
            
            int contagem = analisarMao (baralho, mao, i, tamMao);
            // wprintf(L"A mão tem %d cartas de número %d\n", contagem, i);

            //se tiver, prosseguir para formar dupla sequência
            if (contagem >= 2) {
            continuacaogerarDupSeq (baralho, mao, tamAnterior, tamMao, i);
            }
        }        
    }  
}


int continuacaogerarDupSeq(carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, int posicao) {

    wchar_t* duplasSeqPossiveis = (wchar_t*)malloc(sizeof(wchar_t) * tamAnterior);
    if (duplasSeqPossiveis == NULL) {
        free(duplasSeqPossiveis);
        return -1;
    }

    bool existe = false;
    int tamanho = tamAnterior; // Correção aqui
    int posSequencia = 1;
    int posAnt = posicao;
    duplasSeqPossiveis[0] = mao[posicao]; //o primeiro elemento do array recebe o caracter da posicao da mao

    for (int j = posicao; j < tamMao - 1 && tamanho > 0; j++) // Correção aqui
    {
        if (numeroCarta(baralho, mao[posAnt]) == (numeroCarta(baralho, mao[j + 1])))
        {
            duplasSeqPossiveis[posSequencia] = mao[j + 1];
            posSequencia++;
            tamanho--;

            if (j + 2 < tamMao && numeroCarta(baralho, mao[posAnt]) == (numeroCarta(baralho, mao[j + 2])) - 1) // Correção aqui
            {
                posAnt = j + 1;
                duplasSeqPossiveis[posSequencia] = mao[j + 2]; // Correção aqui
                posSequencia++;
                tamanho--;
            }
        }
    }

    if (tamanho == 0) existe = true;

    if (existe)
    {
        for (int i = 0; i < tamAnterior; i++)
        {
            if (i == tamAnterior - 1) wprintf(L"%lc\n", duplasSeqPossiveis[i]);
            else wprintf(L"%lc ", duplasSeqPossiveis[i]);
        }
    }

    free(duplasSeqPossiveis);

    return 0;
}

