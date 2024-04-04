#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>
#include "funcoes.h"
#include "cartas.h"

void lerConjunto (wchar_t mao[], int quantidade, carta baralho[],wchar_t ordenadoNum[]) {
    int maisAlto=ordenadoNum[quantidade-1];
    int j=(maisAlto*4)-1; //j é a posiçao no baralho da maior carta
    int limj=(maisAlto*4)-4; //a posiçao da carta de menor naipe
    wchar_t maior=0; //carta para ser impressa
    bool encontrada=false;

    //vai comparar as cartas todas da mao, com as quatro naipes da carta de maior numero, de forma decrescente até encontrar a igual

    int i=0;
    while (encontrada==false && j!=limj)
    { 
        if (mao[i]==baralho[j].codigo) //caso o codigo da carta seja igual á carta do baralho
        {   
            maior=mao[i];
            encontrada=true;
        }
        else if (i==quantidade-1) //se nenhuma das cartas for igual á carta do baralho, volta a zero, e compara com a proxima menor carta do baralho
        {
            i=0; 
            j--;
        }
        else i++;
    }

    wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n",quantidade, maior);
    
}

void lerSequencia (wchar_t mao[], int quantidade, carta baralho[],wchar_t ordenadoNum[]) {
    int maisAlto=ordenadoNum[quantidade-1];
    int j=(maisAlto*4)-1; //j é a posiçao no baralho da maior carta
    int limj=(maisAlto*4)-4; //a posiçao da carta de menor naipe
    wchar_t maior; //carta para ser impressa
    bool encontrada=false;
    //vai comparar as cartas todas da mao, com as quatro naipes da carta de maior numero, de forma decrescente até encontrar a igual

    int i=0;
    while (encontrada==false && j!=limj)
    { 
        if (mao[i]==baralho[j].codigo) //caso o codigo da carta seja igual á carta do baralho
        {   
            maior=mao[i];
            encontrada=true;
        }
        else if (i==quantidade-1) //se nenhuma das cartas for igual á carta do baralho, volta a zero, e compara com a proxima menor carta do baralho
        {
            i=0; 
            j--;
        }
        else i++;
    }
    wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n", quantidade, maior);

}

void lerDuplaSequencia (wchar_t mao[], int quantidade, carta baralho[], wchar_t ordenadoNum[]) {
    int maisAlto=ordenadoNum[quantidade-1];
    int j=(maisAlto*4)-1; //j é a posiçao no baralho da maior carta
    int limj=(maisAlto*4)-4; //a posiçao da carta de menor naipe
    wchar_t maior=0; //carta para ser impressa
    bool encontrada=false;

    //vai comparar as cartas todas da mao, com as quatro naipes da carta de maior numero, de forma decrescente até encontrar a igual

    int i=0;
    while (encontrada==false && j!=limj)
    { 
        if (mao[i]==baralho[j].codigo) //caso o codigo da carta seja igual á carta do baralho
        {   
            maior=mao[i];
            encontrada=true;
        }
        else if (i==quantidade-1) //se nenhuma das cartas for igual á carta do baralho, volta a zero, e compara com a proxima menor carta do baralho
        {
            i=0; 
            j--;
        }
        else i++;
    }
    
    wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n", (quantidade/2), maior);
}

// Funçao que receba a mão, e verifica se existe alguma combinação
void verificarCombinacao (wchar_t mao[], int quantidade, carta baralho[]) {
    int j=0;
    int maoNum[quantidade];
    bool combDescoberta=false; //Quando for enviada para a funçao da respetiva combinação, é colocada em true e salta as outras verificações

    for (int i = 0; i < 56; i++)
    {
        if (baralho[i].codigo==mao[j]) 
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
        lerConjunto(mao,quantidade,baralho,maoNum);
    }

    //verifica se é sequencia
    bool falhouSequencia=false;
    if (quantidade>=3) 
    {
        for (int i = 0; i < (quantidade-1) && falhouSequencia==false; i++)
        {
            if(maoNum[i+1]-maoNum[i]!=1) falhouSequencia=true;
        }
        if (falhouSequencia==false) 
        {
            combDescoberta=true;
            lerSequencia(mao,quantidade,baralho,maoNum);
        }
    }

    //verifica se é dupla sequencia
    bool falhouDuplaSeq=false;
    if(quantidade>=6)
    {
        for (int i = 0; i < (quantidade-2) && falhouDuplaSeq==false; i=i+2)
        {
            if(maoNum[i]!=maoNum[i+1]) falhouDuplaSeq=true;
            if(maoNum[i+2]-maoNum[i+1]!=1) falhouDuplaSeq=true;
        }
        if (falhouDuplaSeq==false) 
        {
            combDescoberta=true;
            lerDuplaSequencia(mao,quantidade,baralho, maoNum);
        }
    }
    // caso não tenha nenhuma combinacao
    if (combDescoberta==false)
    {
        wprintf(L"Nada!\n");
    }
}
