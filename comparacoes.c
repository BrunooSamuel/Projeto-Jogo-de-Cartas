#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>
#include "funcoes.h"
#include "cartas.h"

void ordenarConjunto(carta baralho[],wchar_t todasMaos[]) {
    wprintf(L"Veio para a ordenar conjunto\n");
    //existe uma função chamada ordenar, definida no funcoes.c, que ordena ints, se precisarem

    //so para nao dar warning de nao estar a usar o baralho e todasMaos
    //tirem quando forem fazer esta função
    if((baralho[1].numero==12345)&&(todasMaos[0]==0x1F41F)) wprintf(L"Ola\n");
    
}

void ordenarSeq(carta baralho[],wchar_t todasMaos[]) {
    wprintf(L"Veio para a ordenar sequencia\n");
    //existe uma função chamada ordenar, definida no funcoes.c, que ordena ints, se precisarem

    //so para nao dar warning de nao estar a usar o baralho e todasMaos
    //tirem quando forem fazer esta função
    if((baralho[1].numero==12345)&&(todasMaos[0]==0x1F41F)) wprintf(L"Ola\n");
}

void ordenarDupSeq(carta baralho[], wchar_t todasMaos[]) {
    wprintf(L"Veio para a ordenar dupla sequencia\n");
    //existe uma função chamada ordenar, definida no funcoes.c, que ordena ints, se precisarem

    //so para nao dar warning de nao estar a usar o baralho e todasMaos
    //tirem quando forem fazer esta função
    if((baralho[1].numero==12345)&&(todasMaos[0]==0x1F41F)) wprintf(L"Ola\n");
}

void compararMaos(carta baralho[], bool combiguais, bool tamiguais, wchar_t todasMaos[], int arrayCombinacoes[]) {
    //se todas as combinações nao forem iguais
    if (combiguais==false || tamiguais==false) wprintf(L"Combinações não iguais!\n");
    else 
    {   
        // se for conjuntos
        if(arrayCombinacoes[0]!=0) ordenarConjunto(baralho,todasMaos);
        // se for sequencias
        else if(arrayCombinacoes[1]!=0) ordenarSeq(baralho,todasMaos);
        // se for dupla sequencias
        else if(arrayCombinacoes[2]!=0) ordenarDupSeq(baralho,todasMaos);
    }
    
}

void GuardarTamanhos(int arrayTamanhos[], int tamanho) {
    int i;
    for(i=0; arrayTamanhos[i]>0;i++);
    arrayTamanhos[i]=tamanho;
}

void CompararTamanhos(int arrayTamanhos[], bool* tamiguais) {
    for (int i = 0; (arrayTamanhos[i+1]>0) && *tamiguais; i++)
    {
        wprintf(L"%d e %d\n", arrayTamanhos[i], arrayTamanhos[i+1]);
        if(arrayTamanhos[i]!=arrayTamanhos[i+1]) *tamiguais=false;
    }
}

void GuardarCombinacao(int arrayCombinacoes[],bool conjunto,bool sequencia,bool duplasequencia) {
    //vai colocar nas posições para depois ser usado na compararCombinacao
    
    if(conjunto) arrayCombinacoes[0]++;
    else if(sequencia) arrayCombinacoes[1]++;
    else if(duplasequencia) arrayCombinacoes[2]++;
    else arrayCombinacoes[3]++;
}

void CompararCombinacao(int arrayCombinacoes[], int linhas, bool *combiguais) {
    //verificar se são conjuntos
    if (arrayCombinacoes[0]==linhas)
    {
        if((arrayCombinacoes[1]!=0)&&(arrayCombinacoes[2]!=0)&&(arrayCombinacoes[3]!=0)) *combiguais=false;
    }
    //verificar se são sequencias
    if (arrayCombinacoes[1]==linhas&&combiguais)
    {
        if((arrayCombinacoes[0]!=0)&&(arrayCombinacoes[2]!=0)&&(arrayCombinacoes[3]!=0)) *combiguais=false;
    }
    //verificar se são dupla sequencias
    if (arrayCombinacoes[2]==linhas&&combiguais)
    {
        if((arrayCombinacoes[0]!=0)&&(arrayCombinacoes[1]!=0)&&(arrayCombinacoes[3]!=0)) *combiguais=false;
    }
    //verificar se existe alguma linha que não é nenhuma combinação
    if (arrayCombinacoes[3]!=0&&combiguais) *combiguais=false;

}