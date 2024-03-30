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

    setlocale(LC_CTYPE, "C.UTF-8");
    wchar_t s;
    wscanf(L"%C", &s);
    wprintf(L"O símbolo digitado foi: %C\n", s);
    wprintf(L"O Codigo é digitado foi: %x\n", s);
    
*/

void lerMao() {
    setlocale(LC_CTYPE, "C.UTF-8");
    wchar_t mao[14]={0};
    wchar_t c;
    //funcao que coloca as cartas recebidas no array mao
    //fgetws(mao, sizeof(mao)/sizeof(wchar_t), stdin);
    wscanf(L"%C", &c);
    wprintf(L"O símbolo digitado foi: %C\n", c);
    wprintf(L"O Codigo é digitado foi: %x\n", c);

    mao[0]=c;

    wprintf(L"Você digitou: %ls\n", mao);

    wprintf(L"Saiu da lerMao\n");
}


// FUNCAO DE LIMPEZA, N SEI PQ QUE FUNCIONA MAS FUNCIONA
void limpar() {
    setlocale(LC_CTYPE, "C.UTF-8");
    wchar_t limpeza;
    wscanf(L"%C", &limpeza);
}
