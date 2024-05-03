#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

int cartaIsolada (carta baralho[], wchar_t mao[], int valorCartaMaisAlta, int tamMao, int numReis, bool *jaImprimiu) {
    wchar_t* conjunto = (wchar_t*)malloc (sizeof(wchar_t)*tamMao);
    if (conjunto == NULL) {
        free (conjunto);
        free (baralho);
        free (mao);
        return -1;
    }
    int pos=0;
    for (int i = 0; i < tamMao; i++)
    {
        if (valorDaCarta(baralho,mao,i)>valorCartaMaisAlta) 
        {
            conjunto[pos]=mao[i];
            pos++;
        }
    }

    if (pos==0 && (numReis==0 || numReis==4)) wprintf(L"PASSO\n");
    else if (pos!=0)
    {
        (*jaImprimiu)=true;

        int i;
        for (i = 0; i < pos; i++)
        {
            wprintf(L"%lc\n",conjunto[i]);
        }
    }

    free (conjunto);
    return 0;
}


void gerarConjunto (carta baralho[], wchar_t mao[], int valorCartaMaisAlta, int numeroMaisAlta, int tamAnterior, int tamMao, int numReis, bool *jaImprimiu) {
    bool existeConjunto=false;

    for (int i = numeroMaisAlta; i <= 14; i++)
    {
        int contagem=analisarMao (baralho, mao, i, tamMao);
        //wprintf(L"A mão tem %d cartas de número %d\n", contagem, i);

        if (contagem==tamAnterior) 
            {
            //wprintf(L"Pode haver conjunto no numero %d, pq tem %d cartas\n", i, contagem);
            existeConjunto=true;
            ContinuacaoGerarConjunto (baralho, mao, i, tamAnterior, tamMao, valorCartaMaisAlta);
        }
        else if (contagem>tamAnterior) 
        {
            existeConjunto=true;
            variosConjuntos(baralho, mao, i, contagem, tamAnterior, tamMao, valorCartaMaisAlta);
        }
    }
    
    
    if (!(*jaImprimiu) && !existeConjunto && (numReis==0 || numReis==4)) wprintf(L"PASSO\n");
}

//Caso so haja uma hipotese de impressao
int ContinuacaoGerarConjunto (carta baralho[], wchar_t mao[], int numero, int tamAnterior, int tamMao, int valorCartaMaisAlta) {
    bool encontrou=false;
    int posicao=0;

    wchar_t* conjuntoAtual = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
    if (conjuntoAtual == NULL) {
        free (conjuntoAtual);
        free (baralho);
        free (mao);
        return -1;
    }
    for (int i = 0; i < tamMao && posicao<tamAnterior; i++)
    {
        for (int k = (numero*4)-4; k <= (numero*4)-1 && !encontrou; k++)
        {
            //wprintf(L"Comparando %lc e %lc\n", mao[i],baralho[k].codigo);
            if (mao[i]==baralho[k].codigo) 
            {
                conjuntoAtual[posicao]=mao[i];
                posicao++;
                encontrou=true;
            }
        }
        encontrou=false;
    }

    int valorConjuntoAtual=valorDaCartaMaisAlta (baralho, conjuntoAtual, tamAnterior);
    //wprintf(L"Conjunto atual -> %ls\nvalores %d e %d\n", conjuntoAtual, valorConjuntoAtual,valorCartaMaisAlta);
    if (posicao == tamAnterior && valorConjuntoAtual > valorCartaMaisAlta)
    {
        imprimirConjuntos (conjuntoAtual, tamAnterior);
    }

    free (conjuntoAtual);
    return 0;
}

int variosConjuntos(carta baralho[], wchar_t mao[], int numero, int quantidade, int tamAnterior, int tamMao, int valorCartaMaisAlta) {
    wchar_t* conjuntoTotal = (wchar_t*)malloc (sizeof(wchar_t)*quantidade);
    if (conjuntoTotal == NULL) {
        libertar (baralho, mao, conjuntoTotal);
        return -1;
    }
    bool encontrou=false;
    int posicao=0;
   
    //coloca todas as cartas no array para serem usadas nos varios conjuntos
    for (int i = 0; i < tamMao && posicao<quantidade; i++)
    {
        for (int k = (numero*4)-4; k <= (numero*4)-1 && !encontrou; k++)
        {
            if (mao[i]==baralho[k].codigo) 
            {
                conjuntoTotal[posicao]=mao[i];
                posicao++;
                encontrou=true;
            }
        }
        encontrou=false;
    }
    wchar_t* conjunto = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
    if (conjunto == NULL) {
        free (conjunto);
        libertar (baralho, mao, conjuntoTotal);
        return -1;
    }
        
    if (tamAnterior==2) conjuntosTamanho2 (baralho, conjuntoTotal, conjunto, posicao, valorCartaMaisAlta);
    else conjuntosTamanho3 (baralho, conjuntoTotal, conjunto, valorCartaMaisAlta);

    free(conjunto);
    free(conjuntoTotal);
    return 0;
}

void conjuntosTamanho2 (carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int quantidade, int valorCartaMaisAlta) {
    //quantidade de cartas pode ser 3 ou 4
    int p; //primeira carta
    int s; // segunda carta
    int posicaoPfinal=quantidade-2; //ultima posicao da primeira carta
    for (p=0; p <= posicaoPfinal;p++) 
    {            
        int posicaoSfinal=quantidade-1;
        conjunto[0]=conjuntoTotal[p];         
        for (s = p + 1; s <= posicaoSfinal; s++) 
        {
            conjunto[1]=conjuntoTotal[s];
            if (valorDaCartaMaisAlta(baralho,conjunto,2)>valorCartaMaisAlta) {imprimirConjuntos (conjunto, 2);}
        }
    }
}

void conjuntosTamanho3(carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int valorCartaMaisAlta) {
    //quantidade de cartas é sempre 4
    int p; //primeira carta
    int s; // segunda carta
    int t; //terceira carta
    int posicaoPfinal=1; //ultima posicao da primeira carta
    for (p=0;p <= posicaoPfinal;p++) 
    {            
        int posicaoSfinal=2;
        int posicaoTfinal=3;
        conjunto[0]=conjuntoTotal[p];            
        for (s = p + 1; s <= posicaoSfinal; s++) 
        {
            conjunto[1]=conjuntoTotal[s];
            for (t = s + 1; t <= posicaoTfinal; t++)
            {
                conjunto[2]=conjuntoTotal[t];
                if (valorDaCartaMaisAlta(baralho,conjunto,3)>valorCartaMaisAlta) {imprimirConjuntos (conjunto, 3);}
            }
        }
    }
}

void imprimirConjuntos (wchar_t mao[], int tamAnterior) {
    int i;

    for (i = 0; i < tamAnterior-1; i++)
    {
        wprintf(L"%lc ", mao[i]);
    }
    wprintf(L"%lc\n", mao[i]);
}