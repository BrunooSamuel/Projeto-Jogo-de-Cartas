#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

//AUMENTA A FIGURA DE UM ARRAY INTEIRO MAS COLOCA NO NAIPE ESPADAS
void aumentarFigura (carta baralho[], wchar_t jogada[], int tamanho) {
    bool encontrado=false;
    int naipe;
    int difEspadas;
    for (int i = 0; i < tamanho; i++)
    {
        for (int k = 0; k < 52 && !encontrado; k++)
        {
            if (jogada[i]==baralho[k].codigo) 
            {
                naipe=baralho[k].naipe;
                difEspadas=5-naipe;
                jogada[i]=baralho[k+difEspadas].codigo;
                encontrado=true;
            }
        }
        encontrado=false;
    }
}

void colocarNaipeEspadas (carta baralho[],wchar_t *carta) {
    bool encontrado=false;
    int naipe;
    int difEspadas;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if (*carta==baralho[k].codigo) 
        {
            naipe=baralho[k].naipe;
            difEspadas=1-naipe;
            *carta=baralho[k+difEspadas].codigo;
            encontrado=true;
        }
    }
}

void aumentarNaipeCarta (carta baralho[],wchar_t *carta) {
    bool encontrado=false;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if (*carta==baralho[k].codigo) 
        {
            *carta=baralho[k+1].codigo;
            encontrado=true;
        }
    }
}

int numeroCartasEmComum (wchar_t jogada[], wchar_t mao[] ,int tamAnterior, int tamMao) {
    int r=0;
    for (int k = 0; k < tamAnterior; k++)
    {
        for (int i = 0; i < tamMao; i++)
        {
            if(mao[i]==jogada[k]) r++;
        }
    }
    return r;
}

bool cartaExiste (wchar_t mao[], wchar_t carta) {
    bool r=false;
    for (int i = 0; i < 56 && !r; i++)
    {
        if (mao[i]==carta) r=true;
    }
    return r;
}

void colocarSequenciaNaipeEspadas (carta baralho[], wchar_t *jogada, int tamAnterior) {
    for (int i = 0; i < tamAnterior; i++)
    {
        colocarNaipeEspadas (baralho, &jogada[i]);
    }
}

bool verificarSequenciaProximoNaipe (carta baralho[], wchar_t jogada[], wchar_t mao[] ,int tamAnterior, int tamMao, int valorMaisAlto) {
    int contagem=0;
    bool r=false;
    bool existe=false;

    for (int i = 0; i < tamAnterior; i++)
    {
        for (int j = 0; j < tamMao && !existe; j++)
        {
            if (jogada[i]==mao[j]) 
            {
                contagem++;
                existe=true;
            }
        }
        existe=false;
    }
    
    if (contagem==tamAnterior) 
    {
        int valorJogada=valorDaCartaMaisAlta (baralho, jogada, tamAnterior);
        if (valorJogada>valorMaisAlto) r=true;
    }

    return r;
}

void gerarPermutacoes(carta baralho[], wchar_t mao[], wchar_t *jogada, int numero, int posicao, int tamanho, int tamanhoMao, int valorMaisAlto, bool *jaImprimiu) {
    //wprintf(L"posicao %d e tamanho %d\n", posicao, tamanho);
    //se chegar no fim, imprime
    if (posicao == tamanho) {
        bool imprimir=verificarSequenciaProximoNaipe (baralho, jogada, mao, tamanho, tamanhoMao, valorMaisAlto);
        if (imprimir) {(*jaImprimiu)=true; funcaoImprimir(jogada, tamanho);}
        return;
    }

    for (int i = 0; i < 4; i++) {
        jogada[posicao] = baralho[numero * 4 + i].codigo; 
        gerarPermutacoes(baralho, mao, jogada, numero+1, posicao+1, tamanho, tamanhoMao, valorMaisAlto, jaImprimiu); 
    }
    
}

void gerarSequencia (carta baralho[], wchar_t mao[], wchar_t jogadaAnterior[], int valorCartaMaisAlta, int tamAnterior, int tamMao, int numReis) {
    bool jaImprimiu=false;

    int limite=11-numeroCarta (baralho, jogadaAnterior[tamAnterior-1]); //limite para o while la embaixo
    colocarSequenciaNaipeEspadas (baralho, jogadaAnterior, tamAnterior);

    int numero=numeroCarta(baralho, jogadaAnterior[0]);
    gerarPermutacoes(baralho, mao, jogadaAnterior, numero-1, 0, tamAnterior, tamMao, valorCartaMaisAlta, &jaImprimiu);

    while (limite>=0) 
    {   
        //wprintf(L"Limite -> %d\n", limite);
        numero=numeroCarta(baralho, jogadaAnterior[0]);
        gerarPermutacoes(baralho, mao, jogadaAnterior, numero, 0, tamAnterior, tamMao, valorCartaMaisAlta, &jaImprimiu);
        limite--;
    }

    if ((!jaImprimiu) && (numReis==0 || numReis==4)) wprintf(L"PASSO\n");
}