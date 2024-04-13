#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include "funcoes.h"
#include "cartas.h"

//arranja os pares numero e naipe de uma mao
void arranjaPar (carta baralho[], wchar_t mao[], int comprimento, int *numeros, int *naipes) {
    bool encontrado=false;
    for (int i = 0; i < comprimento; i++)
    {
        encontrado=false;
        for (int k = 0; k < 56 && !encontrado; k++)
        {
            if(mao[i]==baralho[k].codigo)  
            {
                numeros[i]=baralho[k].numero;
                naipes[i]=baralho[k].naipe;
                encontrado=true;
            }
        } 
    }  
}

//troca a posicao de dois int num array
void trocarPosicoes(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

void ordenaPares (int comprimento, int *numeros, int *naipes) {

    for (int i = 0; i < comprimento - 1; i++) 
    {
        for (int j = 0; j < comprimento - i - 1; j++) 
        {
            if (numeros[j] > numeros[j + 1] || (numeros[j] == numeros[j + 1] && naipes[j] > naipes[j + 1])) 
            {
                trocarPosicoes(&numeros[j], &numeros[j + 1]);
                trocarPosicoes(&naipes[j], &naipes[j + 1]);
            }
        }
    }
    // resumindamente, ele a cada loop, vai ordenando menos cartas, por que vai "empurrando" as maiores para a frente
}

void parParaCarta (carta baralho[], wchar_t *mao, int comprimento, int *numeros, int *naipes) {
    for (int i = 0; i < comprimento; i++)
    {
        for (int k = 0; k < 56; k++)
        {
            if(baralho[k].numero==numeros[i] && baralho[k].naipe==naipes[i]) 
            {
                mao[i]=baralho[k].codigo;
            }
        }
    }
}

void ordenarMao (carta baralho[], wchar_t *mao, int comprimento) {
    int numeros[comprimento];
    int naipes[comprimento];
    arranjaPar(baralho, mao, comprimento, numeros, naipes);
    ordenaPares(comprimento, numeros, naipes);
    parParaCarta (baralho, mao, comprimento, numeros, naipes);
}

void ordenarTudo (carta baralho[], wchar_t *todasMaos, int comprimento, int linhas) {
    for (int i = 0; i < linhas; i++)
    {
        ordenarMao(baralho,&todasMaos[i*14], comprimento);
    }
}