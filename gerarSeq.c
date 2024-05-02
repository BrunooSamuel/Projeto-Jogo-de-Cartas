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

int verificarSequenciaProximoNaipe (carta baralho[], wchar_t *jogada, wchar_t mao[] ,int tamAnterior, int tamMao, int valorMaisAlto) {
    bool parar=false;

    wchar_t* seq = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
    if (seq == NULL) {
        free (seq);
        return -1;
    }
    wcscpy(seq, jogada);
    imprimirSequencias(seq, tamAnterior);
    //altera a carta
    for (int i = 0; i < tamAnterior; i++)
    {
        aumentarNaipeCarta(baralho, &seq[i]);
        if (cartaExiste(mao,seq[i])) {
            parar=true;
            jogada[i]=seq[i];
        }
    }

    if (parar) 
    {
        imprimirSequencias(seq, tamAnterior);

        int quantidadeCartas=numeroCartasEmComum (jogada, mao, tamAnterior, tamMao);
        if (quantidadeCartas==tamAnterior && valorDaCartaMaisAlta(baralho,jogada,tamAnterior)>valorMaisAlto) 
        {
            imprimirSequencias(jogada, tamAnterior);
        }
    }

    free (seq);
    return 0;
}

// Função para gerar todas as permutações possíveis de um array de caracteres
void gerar_permutacoes(carta baralho[], wchar_t *jogada, int posicao, int fim) {
    if (posicao == fim) {
        wprintf(L"%ls\n", jogada); // Imprime a permutação atual
        return;
    }

    for (int i = posicao; i <= fim; i++) {
        aumentarNaipeCarta (baralho, &jogada[i]);
        gerar_permutacoes(baralho, jogada, posicao, fim); // Chama recursivamente a função para a próxima posição
        aumentarNaipeCarta (baralho, &jogada[i]);
    }
}

void gerarSequencia (carta baralho[], wchar_t mao[], wchar_t jogadaAnterior[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);

    int limite=14-numeroMaisAlta; //limite para o while la embaixo

    colocarSequenciaNaipeEspadas (baralho, jogadaAnterior, tamAnterior);
    int quant=numeroCartasEmComum (jogadaAnterior, mao, tamAnterior, tamMao);
    //imprimirSequencias(jogadaAnterior, tamAnterior);
    if (quant==tamAnterior && valorDaCartaMaisAlta(baralho,jogadaAnterior,tamAnterior)>valorCartaMaisAlta) imprimirSequencias(jogadaAnterior, tamAnterior);
    while (limite>=0) 
    {   
        wprintf(L"Limite -> %d\n", limite);

        aumentarFigura (baralho, jogadaAnterior, tamAnterior);
        //imprimirSequencias(jogadaAnterior, tamAnterior);

        //gerar_permutacoes(baralho, jogadaAnterior, 0, tamAnterior);
        //verificarSequenciaProximoNaipe (baralho, jogadaAnterior, mao, tamAnterior, tamMao, valorCartaMaisAlta);
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