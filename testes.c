#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "funcoes.h"
#include "cartas.h"

void imprimir(int t, carta baralho[]) { // AINDA NAO FUNCIONA
    setlocale(LC_CTYPE, "C.UTF-8");

    for (int i = 0; i < 56; i++) {
        if (baralho[i].numero == t) {

            wchar_t c = baralho[i].codigo;
    	    wprintf(L"%C\n", c);
        }
    } 
 
}

/* 
    ESQUELETO DE WCHAR

<<<<<<< Updated upstream
    wchar_t symbol;
    wscanf(L"%C", &symbol);
    wprintf(L"O símbolo digitado foi: %C\n", symbol);
    wprintf(L"O Codigo é digitado foi: %x\n", symbol);
=======
    setlocale(LC_CTYPE, "C.UTF-8");
    wchar_t s;
    wscanf(L"%C", &s);
    wprintf(L"O símbolo digitado foi: %C\n", s);
    wprintf(L"O Codigo é digitado foi: %x\n", s);
>>>>>>> Stashed changes
    
*/

void lerMao() {

    setlocale(LC_CTYPE, "C.UTF-8");
<<<<<<< Updated upstream
    printf("Chegou a lerMao\n");

    wchar_t car;
    wscanf(L"%lc", &car);
    wprintf(L"Simbolo: %lc\n", car);
    wprintf(L"Codigo: %x\n", car);

    printf("Saiu da lerMao\n");
}

=======
    wchar_t mao[14]={0};

    //funcao que coloca as cartas recebidas no array mao
    fgetws(mao, 14, stdin);


    wprintf(L"Está na mao: %ls\n", mao);
    for (int i = 0; mao[i+1]!='\0'; i++)
    {
        wprintf(L"Os símbolos são: %x\t", mao[i]);
    }
    wprintf(L"\n");
}


// FUNCAO DE LIMPEZA, N SEI PQ QUE FUNCIONA MAS FUNCIONA
void limpar() {
    setlocale(LC_CTYPE, "C.UTF-8");
    wchar_t limpeza;
    wscanf(L"%C", &limpeza);
}
>>>>>>> Stashed changes
