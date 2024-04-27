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

//Esta função verifica a quantidade de cartas do mesmo numero a partir de um certo numero
void analisarMao (carta baralho[], wchar_t mao[], int numero, int tamanho) {
    bool passou=false;
    int pos=0;
    int t;
    while (numero<=14)
    {
        int contagem=0;
        while ((pos < tamanho) && !passou)
        {
            t=numeroCarta(baralho, mao[pos]);
            if (t<numero) pos++;
            else if (t==numero) {contagem++; pos++;}
            else if(t>numero) {passou=true;}
        }
        if (t>=numero) wprintf(L"A mão tem %d cartas de número %d\n", contagem, numero);
        passou=false;
        numero++;
    }
}

void gerarConjunto (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Conjunto\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    analisarMao (baralho, mao, numeroMaisAlta, tamMao);

}

void gerarSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Sequencia\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    analisarMao (baralho, mao, numeroMaisAlta, tamMao);
}

void gerarDuplaSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Dupla Sequencia\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    analisarMao (baralho, mao, numeroMaisAlta, tamMao);
}