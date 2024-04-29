#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

int numeroCarta (carta baralho[], wchar_t carta) {
    int r;
    bool encontrado=false;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if(carta==baralho[k].codigo)  
        {
            r=baralho[k].numero;
            encontrado=true;
            //wprintf(L"O numero é %d\n", r);
        }
    } 
    return r;
}

//Esta função verifica a quantidade de cartas do mesmo numero
int analisarMao (carta baralho[], wchar_t mao[], int numero, int tamanho) {
    bool passou=false;
    int pos=0;
    int t;
    int contagem=0;

    while ((pos < tamanho) && !passou)
    {
        t=numeroCarta(baralho, mao[pos]);
        if (t<numero) pos++;
        else if (t==numero) {contagem++; pos++;}
        else if(t>numero) {passou=true;}
    }
    //wprintf(L"A mão tem %d cartas de número %d\n", contagem, numero);
    return contagem;
}

void gerarConjunto (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);
    for (int i = numeroMaisAlta; i <= 14; i++)
    {
        int contagem=analisarMao (baralho, mao, i, tamMao);
        // wprintf(L"A mão tem %d cartas de número %d\n", contagem, i);

        if (contagem>=tamAnterior) 
        {
            //wprintf(L"Pode haver conjunto no numero %d, pq tem %d cartas\n", i, contagem);
            criarConjuntos (baralho, mao, i, contagem, tamAnterior, tamMao, valorCartaMaisAlta);
        }
    }


}

int criarConjuntos (carta baralho[], wchar_t mao[], int numero, int contagem, int tamAnterior, int tamMao, int valorCartaMaisAlta) {
    bool encontrou=false;
    int tamanho=1;
    bool temMais=true;
    int contagemTamAnterior=tamAnterior;
    int posicao=0;
    int posGuardada;

    wchar_t* conjuntoAtual = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
        if (conjuntoAtual == NULL) {
            free (conjuntoAtual);
            return -1;
        }

    for (int i = 0; i < tamMao; i++)
    {
        for (int k = (numero*4)-4; k <= (numero*4)-1; k++)
        {
            if (mao[i]==baralho[k].codigo) 
            {
                conjuntoAtual[posicao]=mao[i];
                posGuardada=i;
                posicao++;
                encontrou=true;
            }
        }

        if (analisarMao (baralho, mao, numero, tamMao)>tamAnterior) {temMais=true; contagemTamAnterior--;}
        else temMais=false;

        if (encontrou && posicao == tamAnterior) 
        {
            if (valorDaCartaMaisAlta (baralho, conjuntoAtual, tamAnterior) > valorCartaMaisAlta) 
            {
                imprimirConjuntos (conjuntoAtual, tamAnterior);
            }
            tamanho++;
            posicao=0;
        }

        /*
        if (temMais && tamAnterior!=1) 
        {
            for (int o = tamAnterior-1; o>=0; o--)
            {
                if (numeroCarta(baralho,conjuntoAtual[o])==numeroCarta(baralho,mao[posGuardada])) 
                {
                    wchar_t temp=conjuntoAtual[o];
                    conjuntoAtual[o]=mao[posGuardada];
                    imprimirConjuntos (conjuntoAtual, tamAnterior);
                    conjuntoAtual[o]=temp;
                } 
            }  
        }
        */

        // Reinicializa o conjuntoAtual
        memset(conjuntoAtual, 0, sizeof(wchar_t)*tamAnterior);
    }

    free (conjuntoAtual);
    return 0;
}

void imprimirConjuntos (wchar_t mao[], int tamAnterior) {
    int i;
    for (i = 0; i < tamAnterior-1; i++)
    {
        wprintf(L"%lc ", mao[i]);
    }
    wprintf(L"%lc\n", mao[i]);
}

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
        if (encontrou && (numero+k-1)>=numeroMaisAlta) criarSequencias(baralho, mao, tamAnterior, tamMao, i);
    }
    
}

int criarSequencias(carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, int posicao) {
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

void gerarDuplaSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Dupla Sequencia\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    int contagem=analisarMao (baralho, mao, numeroMaisAlta, tamMao);
    wprintf(L"A mão tem %d cartas de número %d\n", contagem, numeroMaisAlta);
}