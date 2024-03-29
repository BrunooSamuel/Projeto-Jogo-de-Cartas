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
    setlocale(LC_CTYPE, "C.UTF-8");
    printf("Chegou a lerMao\n");

    wchar_t car;
    wscanf(L"%lc", &car);
    wprintf(L"Simbolo: %lc\n", car);
    wprintf(L"Codigo: %x\n", car);

    printf("Saiu da lerMao\n");
}

