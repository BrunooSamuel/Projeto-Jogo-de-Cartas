#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>
#include "funcoes.h"
#include "cartas.h"

bool compararTamanhos(int array[], int total) {
    
    // so imprime para ver se está a guardar corretamente
    /*
    for (int i = 0; i < total; i++)
    {
        wprintf(L"%d ", array[i]);
    }
    wprintf(L"\n");
    */

    int r=true;
    //compara
    for (int i = 0; i < (total-1) && r; i++)
    {
        if (array[i]!=array[i+1]) r=false;
    }
    
    return r;
}

bool compararCombinacoes(int array[]) {
//pos 0 é relativa a conjuntos, pos 1 a sequencias, pos 2 a dupla sequencias e pos 3 a nada

    // so imprime para ver se está a guardar corretamente
    /*
    wprintf(L"Conjuntos - %d\t", array[0]);
    wprintf(L"Sequencias - %d\t", array[1]);
    wprintf(L"Dupla Sequencias - %d\t", array[2]);
    wprintf(L"Nada - %d\t", array[3]);
    wprintf(L"\n");
    */
    
    int r=true;
    //compara
    if (array[0]!=0) // conjunto
    {
        if (array[1]!=0||array[2]!=0||array[3]!=0) r=false;
    } 
    else if (array[1]!=0) // sequencia
    {
        if (array[0]!=0||array[2]!=0||array[3]!=0) r=false;
    }
    else if (array[2]!=0) // dupla sequencia
    {
        if (array[0]!=0||array[1]!=0||array[3]!=0) r=false;
    }
    else if(array[3]!=0) // se existir algum nada
    {
        r=false;
    }

    return r;
}

void escolherCombinacao(int array[], wchar_t *todasMaos, carta baralho[], int comprimento) {
    if (array[0]!=0) ordenarConjunto(todasMaos, baralho, comprimento);
    else if(array[1]!=0) ordenarSeq(todasMaos, baralho, comprimento);
    else if(array[2]!=0) ordenarDupSeq(todasMaos, baralho, comprimento);
}

void ordenarConjunto(wchar_t *todasMaos, carta baralho[], int comprimento) {
    wprintf(L"Veio para a ordenar conjunto\n");
    //existe uma função chamada ordenar, definida no funcoes.c, que ordena ints, se precisarem

    // teste que imprime para verificar se o todasMaos está correto
        /*
        for (int i = 0; i < linhas; i++) 
        {
            wprintf(L"%.*ls\n", arrayTamanhos[i], &todasMaos[i * 14]);
        }
        */
  
}

void ordenarSeq(wchar_t *todasMaos, carta baralho[], int comprimento) {
    wprintf(L"Veio para a ordenar sequencia\n");
    //existe uma função chamada ordenar, definida no funcoes.c, que ordena ints, se precisarem

    // teste que imprime para verificar se o todasMaos está correto
        /*
        for (int i = 0; i < linhas; i++) 
        {
            wprintf(L"%.*ls\n", arrayTamanhos[i], &todasMaos[i * 14]);
        }
        */

}

void ordenarDupSeq(wchar_t *todasMaos, carta baralho[], int comprimento) {
    wprintf(L"Veio para a ordenar dupla sequencia\n");
    //existe uma função chamada ordenar, definida no funcoes.c, que ordena ints, se precisarem

    // teste que imprime para verificar se o todasMaos está correto
        /*
        for (int i = 0; i < linhas; i++) 
        {
            wprintf(L"%.*ls\n", arrayTamanhos[i], &todasMaos[i * 14]);
        }
        */

}

