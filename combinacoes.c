#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>
#include "funcoes.h"
#include "cartas.h"

void lerConjunto (wchar_t array[], int quantidade, carta baralho[]) {
    wprintf(L"Veio para a lerConjunto\n");
    
}

void lerSequencia (wchar_t array[], int quantidade, carta baralho[]) {
    wprintf(L"Veio para a lerSequencia\n");

}

void lerDuplaSequencia (wchar_t array[], int quantidade, carta baralho[], ) {




    wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %C\n", quantidade, );
}

// Funçao que receba a mão, e verifica se existe alguma combinação
void verificarCombinacao (wchar_t array[], int quantidade, carta baralho[]) {
    int j=0;
    int maoNum[quantidade];
    bool combDescobrida =false; //Quando for enviada para a funçao da respetiva combinação, é colocada em true e salta as outras verificações

    for (int i = 0; i < 56; i++)
    {
        if (baralho[i].codigo==array[j]) 
        {
            maoNum[j]=baralho[i].numero;
            j++;
            i=0;
        }
    }
    //passa pela funcao ordena para ordenar o array
    ordena(maoNum, quantidade);

    //verifica se é um conjunto
    int soma=0;
    for (int i = 0; i < quantidade; i++)
    {
        soma+=maoNum[i];
    }
    if ((soma/quantidade)==(maoNum[0])) 
    {
        combDescobrida=true;
        lerConjunto(array,quantidade,baralho);
    }

    //verifica se é sequencia
    bool falhouSequencia=false;
    for (int i = 0; i < (quantidade-1) && falhouSequencia==false; i++)
    {
        if(maoNum[i+1]-maoNum[i]!=1) falhouSequencia=true;
    }
    if (falhouSequencia==false) 
    {
        combDescobrida=true;
        lerSequencia(array,quantidade,baralho);
    }

    //verifica se é dupla sequencia
    bool falhouDuplaSeq=false;
    for (int i = 0; i < (quantidade-2) && falhouDuplaSeq==false; i=i+2)
    {
        if(maoNum[i]!=maoNum[i+1]) falhouDuplaSeq=true;
        if(maoNum[i+2]-maoNum[i+1]!=1) falhouDuplaSeq=true;
    }
    if (falhouDuplaSeq==false) 
    {
        combDescobrida=true;
        lerDuplaSequencia(array,quantidade,baralho);
    }

    // caso não tenha nenhuma combinacao
    if (combDescobrida==false)
    {
        wprintf(L"Nada!\n");
    }
}
