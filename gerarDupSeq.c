#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

void colocarNaipeCopas (carta baralho[],wchar_t *carta) {
    bool encontrado=false;
    int naipe;
    int difCopas;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if (*carta==baralho[k].codigo) 
        {
            naipe=baralho[k].naipe;
            difCopas=2-naipe;
            *carta=baralho[k+difCopas].codigo;
            encontrado=true;
        }
    }
}


void colocarDupSeqEspadasCopas (carta baralho[], wchar_t *jogada, int tamAnterior) {
    for (int i = 0; i < tamAnterior; i+=2)
    {
        colocarNaipeEspadas (baralho, &jogada[i]);
        colocarNaipeCopas (baralho, &jogada[i+1]);
    }
}

bool verificarDuplaSequencia (carta baralho[], wchar_t jogada[], wchar_t mao[] ,int tamAnterior, int tamMao, int valorMaisAlto) {
    int contagem=0;
    bool r=false;
    bool existe=false;
    
    for (int i = 0; i < tamAnterior-1; i++)
    {
        if (jogada[i]==jogada[i+1]) return false;
        else if (numeroCarta(baralho, jogada[i])==numeroCarta(baralho, jogada[i+2])) return false;
        else if (valorDaCarta(baralho, jogada[i])>valorDaCarta(baralho, jogada[i+1])) return false;
    }
    
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

void gerarPermutacoesDupSeq(carta baralho[], wchar_t mao[], wchar_t *jogada, int numero, int posicao, int tamanho, int tamanhoMao, int valorMaisAlto,  bool *jaImprimiu) {
    //wprintf(L"posicao %d e tamanho %d\n", posicao, tamanho);
    //se chegar no fim, imprime
    if (posicao == tamanho) {
        bool imprimir=verificarDuplaSequencia (baralho, jogada, mao, tamanho, tamanhoMao, valorMaisAlto);
        if (imprimir) {(*jaImprimiu)=true;funcaoImprimir(jogada, tamanho);}
        return;
    }

    if (!(*jaImprimiu)) 
    {
        if (posicao % 2 == 0) {
            // Aumenta a primeira carta do par
            for (int i = 0; i < 3; i++) // Aumenta apenas três vezes
            {
                jogada[posicao] = baralho[numero * 4 + i].codigo;
                gerarPermutacoesDupSeq(baralho, mao, jogada, numero, posicao + 1, tamanho, tamanhoMao, valorMaisAlto, jaImprimiu);
            }
        } else { // Caso contrário, estamos na segunda carta do par
            // Aumenta a segunda carta do par
            for (int i = 1; i < 4; i++) { // Começa de copas e vai até paus
                if (baralho[numero * 4 + i].codigo!=jogada[posicao-1] && cartaExiste(mao, baralho[numero * 4 + i].codigo)) 
                {
                    jogada[posicao] = baralho[numero * 4 + i].codigo;
                    gerarPermutacoesDupSeq(baralho, mao, jogada, numero + 1, posicao + 1, tamanho, tamanhoMao, valorMaisAlto, jaImprimiu);
                }
                //se encontrar uma combinação possível para de gerar
                if (*jaImprimiu) return;
            }
        }   
    }
    
}

void gerarDuplaSequencia (carta baralho[], wchar_t mao[], wchar_t jogadaAnterior[], int valorCartaMaisAlta, int tamAnterior, int tamMao, int numReis, bool *jaImprimiu) {
    int limite=13-numeroCarta (baralho, jogadaAnterior[tamAnterior-1]); //limite para o while la embaixo

    colocarDupSeqEspadasCopas (baralho, jogadaAnterior, tamAnterior);
    int numero=numeroCarta(baralho, jogadaAnterior[0]);
    gerarPermutacoesDupSeq(baralho, mao, jogadaAnterior, numero-1, 0, tamAnterior, tamMao, valorCartaMaisAlta, jaImprimiu);

    while (limite>=0) 
    {   
        //wprintf(L"Limite -> %d\n", limite);
        numero=numeroCarta(baralho, jogadaAnterior[0]);
        gerarPermutacoesDupSeq(baralho, mao, jogadaAnterior, numero, 0, tamAnterior, tamMao, valorCartaMaisAlta, jaImprimiu);
        limite--;
    }

    if (!(*jaImprimiu) && (numReis==0 || numReis==4)) {(*jaImprimiu)=false; wprintf(L"PASSO\n");}
}


int gerarDSeqSemAnterior (carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, bool *jaImprimiu) {
    wchar_t* array = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
    if (array == NULL) {
        free (array);
        free (baralho);
        free (mao);
        return -1;
    }

    gerarAses(array, tamAnterior);
    colocarDupSeqEspadasCopas (baralho, array, tamAnterior);
    int numero=numeroCarta(baralho, array[0]);
    gerarPermutacoesDupSeq(baralho, mao, array, numero-1, 0, tamAnterior, tamMao, 1, jaImprimiu);

    int limite=14;

    while (limite>0) 
    {   
        //wprintf(L"Limite -> %d\n", limite);
        numero=numeroCarta(baralho, array[0]);
        gerarPermutacoesDupSeq(baralho, mao, array, numero, 0, tamAnterior, tamMao, 1, jaImprimiu);
        limite--;
    }

    if (!(*jaImprimiu)) {
        return -1;
    }
    
    free(array);

    return 0;
}
