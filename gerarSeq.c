#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

// Função para verificar todas as cartas da combinacao na mão do jogador
bool verificarExisteNaMao(wchar_t *mao, wchar_t *comb, int tamanhoMao, int tamanhoComb) {
    int contagem=0;

    while (*comb != L'\0' && tamanhoMao>0) {
        bool encontrou=false;

        for (wchar_t *ptr = mao; *ptr != L'\0' && !encontrou; ++ptr) 
        {
            if (*ptr == *comb) 
            {
                encontrou=true;
                contagem++;
            }
        } 
        // Avançar para a próxima carta da jogada
        comb++;
    }

    if (contagem==tamanhoComb) return true;
    else return false;
}

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

int numeroCartasEmComum ( wchar_t jogada[], wchar_t mao[] ,int tamAnterior, int tamMao) {
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

int verificarSequenciaNaipeEspadas (carta baralho[], wchar_t *jogada, wchar_t mao[] ,int tamAnterior, int tamMao) {
    colocarNaipeEspadas (baralho, jogada);
    int quantidadeCartas= numeroCartasEmComum (jogada, mao, tamAnterior, tamMao);
    return quantidadeCartas;
}

int verificarSequenciaProximoNaipe (carta baralho[], wchar_t *jogada, wchar_t mao[] ,int tamAnterior, int tamMao) {
    for (int i = 0; i < tamAnterior; i++)
    {
        aumentarNaipeCarta(baralho, &jogada[i]);
    }
    
    int quantidadeCartas= numeroCartasEmComum (jogada, mao, tamAnterior, tamMao);

    return quantidadeCartas;
}

int gerarSequencia (carta baralho[], wchar_t mao[], wchar_t jogadaAnterior[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    int limite=numeroMaisAlta-14; //limite para o while la embaixo
    wchar_t* seqArray = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
    if (seqArray == NULL) {
        free (seqArray);
        return -1;
    }

    
    while (limite>=0) {
        int contagemCartas=0;
        for (int i = 0; i < tamAnterior; i++)
        {
            bool figuraExiste=existeFiguraNaMao (baralho, &seqArray[i], mao, tamMao);
            if (figuraExiste) contagemCartas++;
        }
        imprimirSequencias(seqArray,tamAnterior);
        wprintf(L"%d contagem\n", contagemCartas);
    }

    free (seqArray);

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


