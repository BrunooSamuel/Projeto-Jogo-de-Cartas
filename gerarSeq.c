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

bool cartaExiste (carta baralho[], wchar_t carta) {
    bool r=false;
    for (int i = 0; i < 56 && !r; i++)
    {
        if (baralho[i].codigo==carta) r=true;
    }
    return r;
}

int verificarSequenciaNaipeEspadas (carta baralho[], wchar_t *jogada, wchar_t mao[] ,int tamAnterior, int tamMao) {
    for (int i = 0; i < tamAnterior; i++)
    {
        colocarNaipeEspadas (baralho, &jogada[i]);
    }

    int quantidadeCartas= numeroCartasEmComum (jogada, mao, tamAnterior, tamMao);
    return quantidadeCartas;
}

void verificarSequenciaProximoNaipe (carta baralho[], wchar_t *jogada, wchar_t mao[] ,int tamAnterior, int tamMao, int valorMaisAlto) {
    int pos=0;
    bool existe=false;
    bool acabar=false;
    int o=0;
    while (o<15) 
    {
        wprintf(L"o -> %d\n", o);
        while(pos<tamAnterior && !acabar)
        {
            wprintf(L"pos -> %d\n", pos);
            for (int i = 0; i < 4 && !existe; i++)
            {
                aumentarNaipeCarta(baralho, &jogada[pos]);
                if (cartaExiste(baralho,jogada[pos])) existe=true;
            }
            if (!existe) acabar=true;
            else existe=false;
            pos++;
        }
        if (!acabar) 
        {
            int quantidadeCartas=numeroCartasEmComum (jogada, mao, tamAnterior, tamMao);
            if (quantidadeCartas==tamAnterior && valorDaCartaMaisAlta(baralho,jogada,tamAnterior)>valorMaisAlto) 
            {
                imprimirSequencias(jogada, tamAnterior);
            }
        }
        o++;
    }
}

void gerarSequencia (carta baralho[], wchar_t mao[], wchar_t jogadaAnterior[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);

    int limite=14-numeroMaisAlta; //limite para o while la embaixo
    int quant;

    quant=verificarSequenciaNaipeEspadas (baralho, jogadaAnterior, mao, tamAnterior, tamMao);
    //imprimirSequencias(jogadaAnterior, tamAnterior);
    if (quant==tamAnterior && valorDaCartaMaisAlta(baralho,jogadaAnterior,tamAnterior)>valorCartaMaisAlta) imprimirSequencias(jogadaAnterior, tamAnterior);
    while (limite>=0) 
    {   
        wprintf(L"Limite -> %d\n", limite);
        for (int n = 1; n <= 4; n++)
        {
            verificarSequenciaProximoNaipe (baralho, jogadaAnterior, mao, tamAnterior, tamMao, valorCartaMaisAlta);
        }
        limite--;
    }
}

void imprimirSequencias (wchar_t mao[], int tamAnterior) {
    int i;
    for (i = 0; i < tamAnterior-1; i++)
    {
        wprintf(L"%lc ", mao[i]);
    }
    wprintf(L"%lc\n", mao[i]);
}


