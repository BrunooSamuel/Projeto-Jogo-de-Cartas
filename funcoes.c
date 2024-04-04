#include <stdio.h>
#include <locale.h>
#include <wchar.h>
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


void lerMao(carta baralho[]) {
    //posicao no array da mao
    int pos;

    wchar_t mao[14]={0};

    //funcao que coloca as cartas recebidas no array mao
    fgetws(mao, 14, stdin);



    //wprintf(L"Está na mao: %ls\n", mao);
    for (pos = 0; mao[pos+1]!='\0'; pos++)
    {
        //wprintf(L"Os símbolos são: %x\t", mao[pos]);
    }

    //wprintf(L"\n");

    verificarCombinacao (mao, pos, baralho);
}


// FUNCAO DE LIMPEZA
void limpar() {
    wchar_t limpeza;
    wscanf(L"%lc", &limpeza);
}

// Funcao que ordena um array
void ordena(int mao[], int tamanho) {
    int aux[tamanho];
    // O array tem como valor minimo 1 e máximo 14
    int n=1; //numero para ordenar
    int pos=0; //posiçao no array original
    int posA=0; //posicao no array auxiliar

    //ordenaçao no array auxiliar
    for (n=1; n<=14; n++)
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

}   