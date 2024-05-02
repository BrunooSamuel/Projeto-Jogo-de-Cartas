#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gerarConjunto (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    bool existeConjunto=false;
    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);
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
    if (!existeConjunto) wprintf(L"PASSO\n");
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

int gerarSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    
    return 0;
}

//verifica se pode existir sequencia nesse numero
bool verificarSequencia(carta baralho[], wchar_t mao[], int numero, int tamAnterior, int tamMao) {
    bool r=true;
    int limiteNumero = numero-tamAnterior+1;

    while (r && numero>=limiteNumero) {
        if (analisarMao (baralho, mao, numero, tamMao)==0) r=false;
        numero--;
    }
    return r;
}

//Recebe já apenas as cartas para serem geradas as sequencias
int continuacaoGerarSequencias(carta baralho[], wchar_t sequenciaTotal[], int tamAnterior, int tamanho, int valorCartaMaisAlta) {

    
    return 0;
}

void imprimirSequencias (wchar_t mao[], int tamAnterior) {
    int i;
    for (i = 0; i < tamAnterior-1; i++)
    {
        wprintf(L"%lc ", mao[i]);
    }
    wprintf(L"%lc\n", mao[i]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int criarPares () {
    int array[12]={1,2,1,3,2,3,1,4,2,4,3,4};
    return array;
}

int qualPar (carta baralho[], wchar_t primeiro, wchar_t segundo) {
    int pos; //posicao do primeiro numero do par no array do criarPares
    // ja recebe ordenado as cartas
    int p;
    int s;

    for(int i;i<56;i++) {
        if (baralho[i].codigo==primeiro) primeiro=baralho[i].numero;
        else if (baralho[i].codigo==segundo) segundo=baralho[i].numero;
    }

    if (p==1) {
        if (s==2) pos=0;
        else if (s==3) pos=2;
        else pos=6;
    } else if (p==2) {
        if (s==3) pos=4;
        else pos=8;
    } else pos=10;

    return pos;
}

void gerarDuplaSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta); 


}


int continuacaogerarDupSeq(carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, int posicao) {
    

    return 0;
}


