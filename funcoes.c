#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

void imprimir(int t, carta baralho[]) {
    wprintf(L"Começa a imprimir as cartas com numero: %d\n", t);

    for (int i = 0; i < 56; i++) {
        if (baralho[i].numero == t) {

            wchar_t c = baralho[i].codigo;
    	    wprintf(L"%lc\n", c);
        }
    } 

    wprintf(L"Acabou de Imprimir\n");  
}



int lerMao(carta baralho[], int *arrayComb, wchar_t *todasMaos, int posMaos, int arrayTamanhos[]) {


    //32 porque houve testes de dupla sequencia onde o input foi de 28 cartas, +4 de margem
    wchar_t mao[32]={0};

    //funcao que coloca as cartas recebidas no array mao
    if (fgetws(mao, 32, stdin)==NULL) {
        wprintf(L"O Scan da mão é inválido.\n");
        free(arrayTamanhos);
        free(arrayComb);
        free(baralho);
        return -1;
    }

    int tamanho = wcslen(mao)-1;
    //copia o mao para o array todasMaos
    wcsncpy(&todasMaos[posMaos * 32], mao, tamanho);

    /*
    int pos;
    wprintf(L"Está na mao: %ls\n", mao);

    for (pos = 0; mao[pos+1]!='\0'; pos++)
    {
        wprintf(L"Os símbolos são: %x\t", mao[pos]);
    }
    wprintf(L"\n");
    */

    verificarCombinacao (mao, tamanho, baralho, arrayComb);


    return tamanho;
}


// FUNCAO DE LIMPEZA
void limpar() {
    wchar_t limpeza;
    wscanf(L"%lc", &limpeza);
}

// Funcao que ordena um array
void ordena(int mao[], int tamanho) {
    int aux[tamanho];
    // O array tem como valor minimo 1 e máximo 32
    int n=1; //numero para ordenar
    int pos=0; //posiçao no array original
    int posA=0; //posicao no array auxiliar

    //ordenaçao no array auxiliar
    for (n=1; n<=32; n++)
    {   
        for (pos=0; pos<tamanho; pos++)
        {
            if (mao[pos]==n) 
            {
            aux[posA++]=n;
            }
        }
    }
    
    //passar do auxiliar para o array
    for (int i = 0; i < tamanho; i++)
    {
        mao[i]=aux[i];
    }


    /*
    FUNÇÃO TESTE QUE IMPRIME OS NUMEROS PARA VERIFICAR SE ESTÁ ORGANIZADO
    for (int i = 0; i < tamanho; i++)
    {
        wprintf(L"%d\t",aux[i]);
    }
    wprintf(L"\n");
    */
    
}   


void libertarTodas (int *arrayTamanhos, int *arrayComb,wchar_t *todasMaos) {
    free(arrayTamanhos);
    free(arrayComb);
    free(todasMaos);
}


int* alocarArrayInt (int linhas) {
    int *array=malloc((linhas)*sizeof(int)); //aloca memoria para o array
    if (array == NULL) {
        return NULL;
    }
    else {
        memset(array, 0, sizeof(array[0])*linhas); //coloca tudo a 0 no array
        return array;
    }
}

wchar_t* alocarArrayWchar (int *arrayTamanhos,int *arrayComb, int linhas) {
    wchar_t *array=malloc(sizeof(wchar_t)*32*linhas); //array para colocar todas as maos
    if (array == NULL) {
        libertarTodas (arrayTamanhos,arrayComb,array);
        return NULL;
    }
    else return array; 
}


carta* alocarArrayCartas () {
    carta *array = malloc(56 * sizeof(carta));
    if (array == NULL) {
        return NULL;
    }
    else return array;
}

int scanInt () {
    int numero;
    if (wscanf(L"%d", &numero)==EOF) {
        return 1;
    }
    else return numero;
}
