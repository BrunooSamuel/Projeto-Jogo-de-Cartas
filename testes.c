#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "funcoes.h"
#include "cartas.h"

void imprimir(int t, carta baralho[]) { // AINDA NAO FUNCIONA
    setlocale(LC_CTYPE, "C.UTF-8");
    printf("Começa a imprimir as cartas com numero: %d\n", t);

    for (int i = 0; i < 56; i++) {
        if (baralho[i].numero == t) {

            wchar_t c = baralho[i].codigo;
    	    wprintf(L"%C\n", c);
        }
    } 

    printf("Acabou de Imprimir\n");  
}

/* 
    ESQUELETO DE WCHAR

    wchar_t symbol;
    wscanf(L"%C", &symbol);
    wprintf(L"O símbolo digitado foi: %C\n", symbol);
    wprintf(L"O Codigo é digitado foi: %x\n", symbol);
    
*/

void lerMao() {
    printf("Chegou a lerMao\n");
    wchar_t mao[14]={0};

    //funcao que coloca as cartas recebidas no array mao
    fgetws(mao, sizeof(mao)/sizeof(wchar_t), stdin);
    
    wprintf(L"Você digitou: %ls\n", mao);

    printf("Saiu da lerMao\n");
}
