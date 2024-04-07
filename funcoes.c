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


int lerMao(carta baralho[],int arrayCombinacoes[], int arrayTamanhos[], wchar_t todasMaos[][32], int posTodasMaos) {
    //posicao no array da mao
    int pos;
    
    //32 porque houve testes de dupla sequencia onde o input foi de 28 cartas, +4 de margem
    wchar_t mao[32]={0};

    //funcao que coloca as cartas recebidas no array mao
    if (fgetws(mao, 32, stdin)==NULL) {
        wprintf(L"O Scan da mão é inválido.\n");
        return 1;
    }

    //wprintf(L"Está na mao: %ls\n", mao);
    for (pos = 0; mao[pos+1]!='\0'; pos++)
    {
        //wprintf(L"Os símbolos são: %x\t", mao[pos]);
    }

    //wprintf(L"\n");

    //copia a mao, para o array de maos
    wcscpy(todasMaos[posTodasMaos], mao);
    
    GuardarTamanhos(arrayTamanhos, pos);

    verificarCombinacao (mao, pos, baralho,arrayCombinacoes);

    return 0;
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


    /*
    FUNÇÃO TESTE QUE IMPRIME OS NUMEROS PARA VERIFICAR SE ESTÁ ORGANIZADO
    for (int i = 0; i < tamanho; i++)
    {
        wprintf(L"%d\t",aux[i]);
    }
    wprintf(L"\n");
    */
    

}   