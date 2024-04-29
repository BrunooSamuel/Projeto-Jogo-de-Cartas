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
    wprintf(L"Veio para gerar Conjunto\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    int contagem=analisarMao (baralho, mao, numeroMaisAlta, tamMao);
    wprintf(L"A mão tem %d cartas de número %d\n", contagem, numeroMaisAlta);

}
// Criei essa função para usar como teste na gerarSequencia
void imprimirSequencia(wchar_t* sequencia, int tamanho) {
    wprintf(L"Sequência maior encontrada: ");
    for (int i = 0; i < tamanho; i++) {
        wprintf(L"%lc ", sequencia[i]);
    }
    wprintf(L"\n");
}
void gerarSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta, wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Sequencia\n"); 

    int numeroMaisAlta = numeroCarta(baralho, codigoCartaMaisAlta);  
    int contagem = analisarMao(baralho, mao, numeroMaisAlta, tamMao);
    wprintf(L"A mão tem %d cartas de número %d\n", contagem, numeroMaisAlta);

    wchar_t* sequenciaSuperior = NULL;
    int sequenciaAtual = 0;
    int sequenciaMaior = 0;

    for (int i = 0; i < tamMao - 1; i++) {
        wchar_t cartaAtual = mao[i];
        wchar_t proximaCarta = mao[i + 1];
        int numeroCartaAtual = numeroCarta(baralho, cartaAtual);
        int numeroProximaCarta = numeroCarta(baralho, proximaCarta);

        if (numeroProximaCarta == numeroCartaAtual + 1) {
            sequenciaAtual++;

            if (sequenciaAtual > sequenciaMaior) {
                sequenciaMaior = sequenciaAtual;

                free(sequenciaSuperior);

                sequenciaSuperior = (wchar_t*)malloc(sequenciaMaior * sizeof(wchar_t));

              
                for (int j = 0; j < sequenciaMaior; j++) {
                    sequenciaSuperior[j] = mao[i - sequenciaMaior + j + 1];
                }
            }
        } else {
            sequenciaAtual = 0;
        }
    }
    
    if (sequenciaMaior >= tamAnterior) {
        wprintf(L"Encontrada uma sequência superior na mão.\n");
        imprimirSequencia(sequenciaSuperior, sequenciaMaior);
    } else {
        wprintf(L"Não foi encontrada uma sequência superior na mão.\n");
    }

    free(sequenciaSuperior);
}



void gerarDuplaSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Dupla Sequencia\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    int contagem=analisarMao (baralho, mao, numeroMaisAlta, tamMao);
    wprintf(L"A mão tem %d cartas de número %d\n", contagem, numeroMaisAlta);
}