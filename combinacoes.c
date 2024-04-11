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
    while (encontrada==false && j>=limj)
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
    wchar_t maior=0x1F0A1; //carta para ser impressa
    bool encontrada=false;
    //vai comparar as cartas todas da mao, com as quatro naipes da carta de maior numero, de forma decrescente até encontrar a igual

    int i=0;
    while (encontrada==false && j>=limj)
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
    while (encontrada==false && j>=limj)
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

void verificaConjunto(int quantidade, int maoNum[], bool *combinacao) {
    float soma=0;
    for (int i = 0; i < quantidade && !(*combinacao); i++)
    {
        soma+=maoNum[i];
    }
    float calculo=soma/quantidade;
    if ((calculo)==(maoNum[0])) 
    {
        *combinacao=true;
    }
}

void verificaSequencia(int quantidade, int maoNum[], bool *combinacao) {
    
    if (quantidade>=3) 
    {
        bool falhouSequencia=false;

        for (int i = 0; i < (quantidade-1) && falhouSequencia==false && !(*combinacao); i++)
        {
            if(maoNum[i+1]-maoNum[i]!=1) falhouSequencia=true;
        }
        if (falhouSequencia==false) 
        {
            *combinacao=true;
        }
    }
}

void verificaDSequencia(int quantidade, int maoNum[], bool *combinacao) {
    bool falhouDuplaSeq=false;
    if(quantidade>=6)
    {
        for (int i = 0; i < (quantidade-2) && falhouDuplaSeq==false && !(*combinacao); i=i+2)
        {
            if(maoNum[i]!=maoNum[i+1]) falhouDuplaSeq=true;
            if(maoNum[i+2]-maoNum[i+1]!=1) falhouDuplaSeq=true;
        }
        if (falhouDuplaSeq==false) 
        {
            *combinacao=true;
        }
    }
}
// Funçao que receba a mão, e verifica se existe alguma combinação

void verificarCombinacao (wchar_t mao[], int quantidade, carta baralho[], int *arrayComb) {
    int maoNum[quantidade];

    int i=0;
    int j=0;
    while (i < 56)
    {
        if (baralho[i].codigo==mao[j]) 
        {
            maoNum[j]=baralho[i].numero;
            j++;
            i=0;
        }
        else i++;
    }

    //passa pela funcao ordena para ordenar o array
    ordena(maoNum, quantidade);

    //verifica se é um conjunto
    bool conjunto=false; 
    verificaConjunto(quantidade, maoNum, &conjunto);

    if (conjunto) arrayComb[0]++;
    // if (conjunto) lerConjunto(mao,quantidade,baralho,maoNum);


    //verifica se é sequencia
    bool sequencia=false;
    if (conjunto==false) verificaSequencia(quantidade, maoNum, &sequencia);

    if (sequencia) arrayComb[1]++;
    // if (sequencia) lerSequencia(mao,quantidade,baralho,maoNum);


    //verifica se é dupla sequencia
    bool duplasequencia=false;
    if (conjunto==false&&sequencia==false) verificaDSequencia(quantidade, maoNum, &duplasequencia);
    if (duplasequencia) arrayComb[2]++;
    // if (duplasequencia) lerDuplaSequencia(mao,quantidade,baralho,maoNum);


    // caso não tenha nenhuma combinacao
    if (sequencia==false&&conjunto==false&&duplasequencia==false)
    {
        arrayComb[3]++;
        wprintf(L"Nada!\n");
    }

    GuardarCombinacao(arrayCombinacoes,conjunto,sequencia,duplasequencia);
}
