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
    int i;
    for (i = 0; i < comprimento-1; i++) 
    {
        wprintf(L"%lc ", mao[i]);
    }
    wprintf(L"%lc\n", mao[i]);
}

void ordenarTudo (carta baralho[], wchar_t *jogadasAnteriores, int comprimento, int linhas) {
    for (int i = 0; i < linhas; i++)
    {
        ordenarMao(baralho,&jogadasAnteriores[i*32], comprimento);
    }
}

void ultimoValor(carta baralho[], wchar_t *mao,int tamanho, int *valores, int posicao) {
    bool encontrado=false;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if(mao[tamanho]==baralho[k].codigo)  
        {
            valores[posicao]=baralho[k].numero*4+(baralho[k].naipe-4);
            encontrado=true;
        }
    } 
}

void maosCrescente (carta baralho[], wchar_t *jogadasAnteriores,int comprimento, int linhas, int arrayTamanhos[]) {
    int valores[linhas];
    for (int i = 0; i < linhas; i++)
    {
        ultimoValor(baralho, &jogadasAnteriores[i*32], (comprimento-1), valores, i);
    }
    
    for (int i = 0; i < linhas - 1; i++) {
        for (int j = 0; j < linhas - i - 1; j++) {
            if (valores[j] > valores[j + 1]) {
                // Troca os valores das cartas mais altas
                int tInt = valores[j];
                valores[j] = valores[j + 1];
                valores[j + 1] = tInt;

                // Troca as maos
                wchar_t tMao[32];
                wcsncpy(tMao, &jogadasAnteriores[j * 32], 31);
                tMao[31] = L'\0';
                wcsncpy(&jogadasAnteriores[j * 32], &jogadasAnteriores[(j + 1) * 32],31);
                jogadasAnteriores[(j + 1) * 32 + 31] = L'\0';
                wcsncpy(&jogadasAnteriores[(j + 1) * 32], tMao,31);
            }
        }
    }
    imprimeMaosOrdenadas (linhas, arrayTamanhos, jogadasAnteriores);
}

void imprimeMaosOrdenadas (int linhas, int arrayTamanhos[], wchar_t *jogadasAnteriores) {
    // IMPRIME AS MAOS ORDENADAS
    for (int i = 0; i < linhas; i++) 
    {
        int j=0;
        // *indica que a largura é fornecida pelo argumento arrayTamanhos[i]
        for (j = 0; j < arrayTamanhos[i]-1; j++) {
            wprintf(L"%lc ", jogadasAnteriores[i * 32 + j]);
        }
        wprintf(L"%lc", jogadasAnteriores[i * 32 + j]);
        wprintf(L"\n");
    }
}