#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>
#include "funcoes.h"
#include "cartas.h"

void lerConjunto (wchar_t array[], int quantidade, carta baralho[],wchar_t ordenadoNum[]) {
    wprintf(L"Veio para a lerConjunto\n");
    
}

void lerSequencia (wchar_t array[], int quantidade, carta baralho[],wchar_t ordenadoNum[]) {
    wprintf(L"Veio para a lerSequencia\n");

}

void lerDuplaSequencia (wchar_t array[], int quantidade, carta baralho[], wchar_t ordenadoNum[]) {
    int maisAlto=ordenadoNum[quantidade-1];
    int j=(maisAlto*4)-1; //j é a posiçao no baralho da maior carta
    int limj=(maisAlto*4)-4; //a posiçao da carta de menor naipe
    wchar_t maior; //carta para ser impressa
    bool encontrada=false;

    //vai comparar as cartas todas da mao, com as quatro naipes da carta de maior numero, de forma decrescente até encontrar a igual

    for (int i = 0; i < quantidade && encontrada==false && j!=limj; i++)
    { //array é a mao
        if (array[i]==baralho[j].codigo) //caso o codigo da carta seja igual á carta do baralho
        {   
            maior=array[i];
            encontrada=true;
        }
        if (i==quantidade-1) //se nenhuma das cartas for igual á carta do baralho, volta a zero, e compara com a proxima menor carta do baralho
        {
            i=0; 
            j--;
        }
    }
    wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %C\n", (quantidade/2), maior);
}

// Funçao que receba a mão, e verifica se existe alguma combinação
void verificarCombinacao (wchar_t array[], int quantidade, carta baralho[]) {
    int j=0;
    int maoNum[quantidade];
    bool combDescoberta=false; //Quando for enviada para a funçao da respetiva combinação, é colocada em true e salta as outras verificações

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
        combDescoberta=true;
        lerConjunto(array,quantidade,baralho,maoNum);
    }

    //verifica se é sequencia
    bool falhouSequencia=false;
    for (int i = 0; i < (quantidade-1) && falhouSequencia==false; i++)
    {
        if(maoNum[i+1]-maoNum[i]!=1) falhouSequencia=true;
    }
    if (falhouSequencia==false) 
    {
        combDescoberta=true;
        lerSequencia(array,quantidade,baralho,maoNum);
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
        combDescoberta=true;
        lerDuplaSequencia(array,quantidade,baralho, maoNum);
    }

    // caso não tenha nenhuma combinacao
    if (combDescoberta==false)
    {
        wprintf(L"Nada!\n");
    }
}
