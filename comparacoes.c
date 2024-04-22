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


bool verificarJogada(carta baralho[], wchar_t *jogadaJogador, wchar_t *jogadasAnte, int arrayTamanhos[], int tamJogadaJogador, int numAnte) { 

    if (jogadaJogador[0] == L'P') return true;

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
        bool parar=false;
        for(i=numAnte - 1; i>=0 && i > (numAnte-4) && passosEncontrados < 3 && !parar; i--) 
        {
            if (jogadasAnte[i * 32] == L'P') 
            {
                passosEncontrados++;
            }
            else {parar=true; i++;}
        }

        //wprintf(L"Numero de passos %d\n", passosEncontrados);

        if(passosEncontrados == 3)
        {
            verificarCombinacao(jogadaJogador, tamJogadaJogador, baralho, comb);
            return(comb[3] == 0);
        }
        else // caso nao tenha 3 passos
        {
            //wprintf(L"%d e %d\n", arrayTamanhos[i],tamJogadaJogador);
            
            return verificarAux (baralho, jogadaJogador, jogadasAnte, arrayTamanhos, tamJogadaJogador, i, comb);
            
        }
    }
}

bool verificarAux (carta baralho[], wchar_t *jogadaJogador, wchar_t *jogadasAnte, int arrayTamanhos[], int tamJogadaJogador, int i, int *comb) {
    
    if(arrayTamanhos[i] != tamJogadaJogador) return false;

    verificarCombinacao(jogadaJogador, tamJogadaJogador, baralho, comb);
    int valorMao=maiorCartaValor(baralho, jogadaJogador,tamJogadaJogador);

    verificarCombinacao(&jogadasAnte[i*32], tamJogadaJogador, baralho, comb);
    int valorAnte=maiorCartaValor(baralho, &jogadasAnte[i*32],tamJogadaJogador);

    if (valorMao<=valorAnte) return false;
            
    for(i = 0; i < 3; i++)
    {
    if(comb[i] == 2) return true;
    }

    return false;
}

bool verificarJogadacomReis(carta baralho[], wchar_t *jogadaJogador, int numReis, int tamJogadaJogador) {  
    if (wcscmp(jogadaJogador, L"PASSO\n") == 0) return true;

    int comb[4] = {0};
    verificarCombinacao(jogadaJogador, tamJogadaJogador, baralho, comb);
    if (numReis==1) 
    {
        if (comb[0]==1 && tamJogadaJogador==4) return true;
        else if (comb[2]==1 && tamJogadaJogador==6) return true;
        else return false;
    } 
    else if (numReis==2) 
    {
        if (comb[2]==1 && tamJogadaJogador==8) return true;
        else return false;
    } 
    else if (numReis==3) 
    {
        if (comb[2]==1 && tamJogadaJogador==10) return true;
        else return false;
    } 
    else return false;
}