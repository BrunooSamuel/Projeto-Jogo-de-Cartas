#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gerarConjunto (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);
    for (int i = numeroMaisAlta; i <= 14; i++)
    {
        int contagem=analisarMao (baralho, mao, i, tamMao);
        // wprintf(L"A mão tem %d cartas de número %d\n", contagem, i);

        if (contagem==tamAnterior) 
        {
            //wprintf(L"Pode haver conjunto no numero %d, pq tem %d cartas\n", i, contagem);
            ContinuacaoGerarConjunto (baralho, mao, i, tamAnterior, tamMao, valorCartaMaisAlta);
        }
        else if (contagem>tamAnterior) variosConjuntos(baralho, mao, i, contagem, tamAnterior, tamMao, valorCartaMaisAlta);
    }
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
        free (conjuntoTotal);
        free (baralho);
        free (mao);
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
        free (conjuntoTotal);
        free (baralho);
        free (mao);
        return -1;
    }
        
    if (tamAnterior==1) {
        for (int i = 0; i < quantidade; i++)
        {
            conjunto[0]=conjuntoTotal[i];
            imprimirConjuntos (conjunto, tamAnterior);
        }
        
    }
    else if (tamAnterior==2) conjuntosTamanho2 (baralho, conjuntoTotal, conjunto, posicao, valorCartaMaisAlta);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gerarSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Sequencia\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  

    for (int i = 0; i < tamMao; i++)
    {
        int numero= numeroCarta (baralho, mao[i]);
        int contagem=0;
        bool naoTem=false;
        bool encontrou=false;
        int k;
        
        for (k = 0; contagem <= tamAnterior && !naoTem && !encontrou; k++)
        {
            if (contagem == tamAnterior) encontrou=true;
            else 
            {
                int quantidade=analisarMao (baralho, mao, numero+k, tamMao);
                if (quantidade!=0) contagem++;
                else naoTem=true;
            }
        }
        if (encontrou && (numero+k-1)>=numeroMaisAlta) continuacaoGererSequencias(baralho, mao, tamAnterior, tamMao, i);
    }
    
}

int continuacaoGererSequencias(carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, int posicao) {
    wchar_t* sequenciaAtual = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
    if (sequenciaAtual == NULL) {
        free (sequenciaAtual);
        return -1;
    }

    bool existe=false;
    int posSequencia=1;
    int posicaoAntiga=posicao;
    sequenciaAtual[0]=mao[posicao];
    int tamanho=tamAnterior;
    int numero_de_passados=0;

    for (int i = posicao; i < tamMao && tamanho>0; i++)
    {
        if (numeroCarta(baralho,mao[posicaoAntiga])==(numeroCarta(baralho,mao[i+1]))-1) 
        {
            posicaoAntiga=i+1;
            sequenciaAtual[posSequencia]=mao[i+1];
            posSequencia++;
            tamanho--;
        }
        else numero_de_passados++;

    }
    if (tamanho==0) existe=true;

    if (existe) 
    {
        for (int i = 0; i < tamAnterior; i++)
        {
            if (i==tamAnterior-1) wprintf(L"%lc\n", sequenciaAtual[i]);
            else wprintf(L"%lc ", sequenciaAtual[i]);            
        }
    }
    /*
    while (numero_de_passados>0) 
    {
        for (int i = 0; i < tamAnterior; i++)
        {
            if (analisarMao())
            if (i==tamAnterior-1) wprintf(L"%lc\n", sequenciaAtual[i]);
            else wprintf(L"%lc ", sequenciaAtual[i]); 
        }
        numero_de_passados--;
    }
    */
    free(sequenciaAtual);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gerarDuplaSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Dupla Sequencia\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    int contagem=analisarMao (baralho, mao, numeroMaisAlta, tamMao);
    wprintf(L"A mão tem %d cartas de número %d\n", contagem, numeroMaisAlta);
}