#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>
#include "funcoes.h"
#include "cartas.h"

bool compararTamanhos(int array[], int total) {

    // so imprime para ver se está a guardar corretamente
    /*
    for (int i = 0; i < total; i++)
    {
        wprintf(L"%d ", array[i]);
    }
    wprintf(L"\n");
    */

    int r=true;
    //compara
    for (int i = 0; i < (total-1) && r; i++)
    {
        if (array[i]!=array[i+1]) r=false;
    }
    return r;
}

bool compararCombinacoes(int array[]) {
//pos 0 é relativa a conjuntos, pos 1 a sequencias, pos 2 a dupla sequencias e pos 3 a nada

    // so imprime para ver se está a guardar corretamente
    /*
    wprintf(L"Conjuntos - %d\t", array[0]);
    wprintf(L"Sequencias - %d\t", array[1]);
    wprintf(L"Dupla Sequencias - %d\t", array[2]);
    wprintf(L"Nada - %d\t", array[3]);
    wprintf(L"\n");
    */
    
    int r=true;
    //compara
    if (array[0]!=0) // conjunto
    {
        if (array[1]!=0||array[2]!=0||array[3]!=0) r=false;
    } 
    else if (array[1]!=0) // sequencia
    {
        if (array[0]!=0||array[2]!=0||array[3]!=0) r=false;
    }
    else if (array[2]!=0) // dupla sequencia
    {
        if (array[0]!=0||array[1]!=0||array[3]!=0) r=false;
    }
    else if(array[3]!=0) // se existir algum nada
    {
        r=false;
    }

    return r;
}

int maiorCartaValor(carta baralho[], wchar_t *mao,int tamanho) {
    bool encontrado=false;
    int valor=0;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if(mao[tamanho-1]==baralho[k].codigo)  
        {
            valor=baralho[k].numero*4+(baralho[k].naipe-4);
            encontrado=true;
        }
    } 
    return valor;
}


bool verificarJogada(carta baralho[], wchar_t *jogadaJogador, wchar_t *jogadasAnte, int arrayTamanhos[], int tamJogadaJogador, int numAnte)
{  
    int comb[4] = {0};
    if(numAnte == 0)
    {
        verificarCombinacao(jogadaJogador, tamJogadaJogador, baralho, comb);
        return(comb[3] == 0);
    }
    else
    {   
        int i;
        int passosEncontrados = 0;
        for(i = numAnte - 1; wcscmp(&jogadasAnte[i], L"PASSO") == 0; i--) passosEncontrados++;
        if(passosEncontrados == 3)
        {
            verificarCombinacao(jogadaJogador, tamJogadaJogador, baralho, comb);
            return(comb[3] == 0);
        }
        else // caso nao tenha 3 passos
        {
            if(arrayTamanhos[i] != tamJogadaJogador) return false;

            verificarCombinacao(jogadaJogador, tamJogadaJogador, baralho, comb);
            int valorMao=maiorCartaValor(baralho, jogadaJogador,tamJogadaJogador);

            verificarCombinacao(&jogadasAnte[i], tamJogadaJogador, baralho, comb);
            int valorAnte=maiorCartaValor(baralho, &jogadasAnte[i],tamJogadaJogador);

            if (valorMao<=valorAnte) return false;

            if(comb[3] != 0) return false;
            for(i = 0; i < 3; i++)
            {
                if(comb[i] == 2) return true;
                if(comb[i] == 1) return false;
            }
        }
    }
    return false;
}

bool verificarJogadacomReis(carta baralho[], wchar_t *jogadaJogador, wchar_t *jogadasAnte, int arrayTamanhos[], int tamJogadaJogador, int numAnte)
{  
    int comb[4] = {0};
    if(numAnte == 0)
    {
        verificarCombinacao(jogadaJogador, tamJogadaJogador, baralho, comb);
        return(comb[3] == 0);
    }
    else
    {   
        int i;
        int passosEncontrados = 0;
        for(i = numAnte - 1; wcscmp(&jogadasAnte[i], L"PASSO") == 0; i--) passosEncontrados++;
        if(passosEncontrados == 3)
        {
            verificarCombinacao(jogadaJogador, tamJogadaJogador, baralho, comb);
            return(comb[3] == 0);
        }
        else // caso nao tenha 3 passos
        {
            if(arrayTamanhos[i] != tamJogadaJogador) return false;

            verificarCombinacao(jogadaJogador, tamJogadaJogador, baralho, comb);
            int valorMao=maiorCartaValor(baralho, jogadaJogador,tamJogadaJogador);

            verificarCombinacao(&jogadasAnte[i], tamJogadaJogador, baralho, comb);
            int valorAnte=maiorCartaValor(baralho, &jogadasAnte[i],tamJogadaJogador);

            if (valorMao<=valorAnte) return false;

            if(comb[3] != 0) return false;
            for(i = 0; i < 3; i++)
            {
                if(comb[i] == 2) return true;
                if(comb[i] == 1) return false;
            }
        }
    }
    return false;
}