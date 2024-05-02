#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

int* criarPares () {
    int array[12]={1,2,1,3,2,3,1,4,2,4,3,4};
    return array;
}

int qualPar (carta baralho[], wchar_t primeiro, wchar_t segundo) {
    int pos; //posicao do primeiro numero do par no array do criarPares
    // ja recebe ordenado as cartas
    int p;
    int s;

    for(int i;i<56;i++) {
        if (baralho[i].codigo==primeiro) p=baralho[i].numero;
        else if (baralho[i].codigo==segundo) s=baralho[i].numero;
    }

    if (p==1) {
        if (s==2) pos=0;
        else if (s==3) pos=2;
        else pos=6;
    } else if (p==2) {
        if (s==3) pos=4;
        else pos=8;
    } else pos=10;

    return pos;
}

void gerarDuplaSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta); 


}