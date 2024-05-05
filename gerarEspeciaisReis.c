#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"


void gerarAses (wchar_t array[], int tamAnterior) {
    for (int i = 0; i < tamAnterior; i++)
    {
        array[i]=0x1F0A1;
    }
}

int gerarDuplaSeqEspeciaisReis (carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, bool *jaImprimiu) {
    wchar_t* array = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
    if (array == NULL) {
        free (array);
        free (baralho);
        free (mao);
        return -1;
    }
    gerarAses(array, tamAnterior);
    colocarDupSeqEspadasCopas (baralho, array, tamAnterior);
    int numero=numeroCarta(baralho, array[0]);
    gerarPermutacoesDupSeq(baralho, mao, array, numero-1, 0, tamAnterior, tamMao, 1, jaImprimiu);

    int limite=14;
    while (limite>0) 
    {   
        //wprintf(L"Limite -> %d\n", limite);
        numero=numeroCarta(baralho, array[0]);
        gerarPermutacoesDupSeq(baralho, mao, array, numero, 0, tamAnterior, tamMao, 1, jaImprimiu);
        limite--;
    }

    free(array);
    if (!(*jaImprimiu)) wprintf(L"PASSO\n");

    return 0;
}